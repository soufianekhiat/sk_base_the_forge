using System;
using Sharpmake;
using Microsoft.Win32;
using System.IO;
using System.Collections.Generic;

namespace SKBase
{
	static class Extern
	{
		static public string RootPath = @"[project.SharpmakeCsPath]";
		static public string ExternPath = RootPath + @"\extern";
	}

	[Fragment, Flags]
	public enum TargetAPI
	{
		D3D12	= (1 << 0),
		Vulkan	= (1 << 1),
		D3D11	= (1 << 2),
		Wasm	= (1 << 3),
		Null	= (1 << 4)
	}

	[Fragment, Flags]
	public enum BuildType
	{
		Runtime	= (1 << 0),
		Editor	= (1 << 1),
		Full	= (1 << 2),
		Tests	= (1 << 3)
	}

	public class SKBaseTarget : Target
	{
		public SKBaseTarget()
			: base()
		{ }

		public SKBaseTarget(Platform platform, TargetAPI api, Optimization optimization, BuildType buildType)
			: base(platform, DevEnv.vs2019, optimization)
		{
			Api = api;
			Build = buildType;
		}

		public TargetAPI Api;
		public BuildType Build;
	}

	public class CommonSolution : Sharpmake.Solution
	{
		public string SolutionRootPath = @"[solution.SharpmakeCsPath]\..";

		public CommonSolution()
			: base(typeof(SKBaseTarget))
		{ }
	}

	public class CommonProject : Sharpmake.Project
	{
		public string ProjectRootPath = @"[project.SharpmakeCsPath]\..";
		public string TmpPath = @"[project.RootPath]\tmp";
		public string ExternPath = @"[project.RootPath]\extern";
		public string ProjectsPath = @"[project.RootPath]\projects";
		public string OutputPath = @"[project.RootPath]\WorkingDir";

		public CommonProject()
			: base(typeof(SKBaseTarget))
		{
			RootPath = ProjectRootPath;
			SourceFilesExtensions.Add(".inl", ".hpp");
			//CustomProperties.Add("VcpkgEnabled", "false");

			AddTargets(new SKBaseTarget(Platform.win64,
										TargetAPI.D3D12 |
										TargetAPI.Vulkan |
										TargetAPI.Null,
										Optimization.Debug | Optimization.Release,
										BuildType.Runtime | BuildType.Editor | BuildType.Full | BuildType.Tests));
		}

		[Configure()]
		public virtual void ConfigureAll(Configuration conf, SKBaseTarget target)
		{
			conf.Name = "[target.Api]_[target.Optimization]";
			conf.ProjectFileName = "[project.Name]_[target.DevEnv]_[target.Platform]";
			conf.ProjectPath = ProjectsPath + @"\[target.Platform]\[target.Build]\[project.Name]";
			conf.IntermediatePath = @"[project.TmpPath]\[target.Api]\[target.Platform]\[project.Name]\[target.Optimization]";
			conf.TargetPath = @"[project.OutputPath]";
			conf.TargetLibraryPath = @"[project.RootPath]\tmp\lib\[target.Platform]_[target.Api]_[target.Optimization]";

			conf.IncludePaths.Add(@"[project.RootPath]\src");
			conf.IncludePaths.Add(@"[project.RootPath]\");
			conf.IncludePaths.Add(@"[project.ExternPath]");

			conf.Output = Configuration.OutputType.Lib;

			conf.AdditionalCompilerOptions.Add("/bigobj");
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.Inline.AnySuitable);
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.CompileAsWinRT.Disable);
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.RTTI.Disable);
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.FloatingPointExceptions.Disable);
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.FloatingPointModel.Fast);
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.EnhancedInstructionSet.AdvancedVectorExtensions);
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.Exceptions.Disable);
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.Intrinsic.Enable);
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.ConformanceMode.Enable);
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.FavorSizeOrSpeed.FastCode);
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.StructAlignment.Alignment8);

			conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.Latest);

			conf.Options.Add(Sharpmake.Options.Vc.Linker.GenerateDebugInformation.Enable);
			conf.Options.Add(Sharpmake.Options.Vc.Linker.LargeAddress.SupportLargerThan2Gb);

			conf.AdditionalCompilerOptions.Add("/Zc:char8_t");

			conf.AdditionalCompilerOptions.Add("/Zo");

			conf.Defines.Add("eMVDLLExport");
			conf.Defines.Add("NOMINMAX");

			if (target.Build == BuildType.Editor || target.Build == BuildType.Full)
			{
				conf.Defines.Add("__EMV_EDITOR__");
				conf.Defines.Add("__EMV_TOOL__");
				conf.IncludePaths.Add(@"[project.ExternPath]/imgui/");
			}

			if (target.Optimization == Optimization.Debug)
				conf.Defines.Add("__EMV_DEBUG__");
			else
				conf.Defines.Add("__EMV_RELEASE__");
		}

		[Configure(Platform.win64)]
		public virtual void ConfigureWindows(Configuration conf, SKBaseTarget target)
		{
			conf.Defines.Add("_ENABLE_EXTENDED_ALIGNED_STORAGE");
			conf.Defines.Add("__EMV_WIN__");
			//conf.Defines.Add("WIN32"); // Added for SIGAR to map pid_t properly
			conf.LibraryFiles.Add("Wtsapi32"); // Enables applications to receive WTS messages from windows
			conf.AdditionalLinkerOptions.Add("/ignore:4098,4099,4217,4221");
			conf.Defines.Add("WINAPI_FAMILY=WINAPI_FAMILY_DESKTOP_APP");
			conf.Defines.Add("_WIN32_WINNT=0x0600");
			conf.Options.Add(Sharpmake.Options.Vc.Linker.RandomizedBaseAddress.Disable);
		}

		[Configure(Optimization.Debug)]
		public virtual void ConfigureDebug(Configuration conf, SKBaseTarget target)
		{
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.Inline.Disable);
		}

		[Configure(Optimization.Release)]
		public virtual void ConfigureRelease(Configuration conf, SKBaseTarget target)
		{
			conf.Options.Add(Sharpmake.Options.Vc.Compiler.Optimization.MaximizeSpeed);
			conf.Options.Add(Sharpmake.Options.Vc.General.WholeProgramOptimization.LinkTime);
			conf.Options.Add(Sharpmake.Options.Vc.Linker.LinkTimeCodeGeneration.UseLinkTimeCodeGeneration);
			conf.Options.Add(Sharpmake.Options.Vc.Linker.EnableCOMDATFolding.RemoveRedundantCOMDATs);
			conf.Options.Add(Sharpmake.Options.Vc.Linker.Reference.EliminateUnreferencedData);
		}

		[Configure(TargetAPI.D3D11)]
		public virtual void ConfigureD3D11(Configuration conf, SKBaseTarget target)
		{
			conf.Defines.Add("__EMV_GFX_D3D11__");
		}

		[Configure(TargetAPI.D3D12)]
		public virtual void ConfigureD3D12(Configuration conf, SKBaseTarget target)
		{
			conf.Defines.Add("__EMV_GFX_D3D12__");
		}

		[Configure(TargetAPI.Vulkan)]
		public virtual void ConfigureVulkan(Configuration conf, SKBaseTarget target)
		{
			conf.Defines.Add("__EMV_GFX_VULKAN__");
		}

		[Configure(TargetAPI.Wasm)]
		public virtual void ConfigureWasm(Configuration conf, SKBaseTarget target)
		{
			conf.Defines.Add("__EMV_WASM__");
		}

		[Configure(TargetAPI.Null)]
		public virtual void ConfigureNull(Configuration conf, SKBaseTarget target)
		{
			conf.Defines.Add("__EMV_GFX_NULL__");
		}

		[Configure(BuildType.Editor)]
		public virtual void ConfigureEditor(Configuration conf, SKBaseTarget target)
		{
			conf.Defines.Add("__EMV_EDITOR__");
			conf.Defines.Add("__EMV_TOOL__");
		}

		[Configure(OutputType.Lib)]
		public virtual void OutputTypeLib(Configuration conf, SKBaseTarget target)
		{
			if (target.Platform == Platform.win64)
			{
				if (target.Optimization == Optimization.Debug)
					conf.Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDebugDLL);
				else
					conf.Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDLL);
			}

			if (target.Platform == Platform.win64)
				conf.Options.Add(Options.Vc.General.PreferredToolArchitecture.x64);
		}
	}
}
