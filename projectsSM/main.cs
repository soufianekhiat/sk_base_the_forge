using Sharpmake;

[module: Sharpmake.Include("common.cs")]

[module: Sharpmake.Include("API.cs")]

[module: Sharpmake.Include("Empty.cs")]
[module: Sharpmake.Include("01_Transforms.cs")]
[module: Sharpmake.Include("UI_App.cs")]

namespace SKBase
{
	[Sharpmake.Generate]
	public class SKBaseSolution : CommonSolution
	{
		//public string ProjectRootPath = @"[project.SharpmakeCsPath]\..";
		//public string TmpPath = @"[project.RootPath]\tmp";
		public string ExternPath = @"[solution.SolutionRootPath]\extern";
		//public string ProjectsPath = @"[project.RootPath]\projects";
		//public string OutputPath = @"[project.RootPath]\WorkingDir";

		public SKBaseSolution()
		{
			Name = "SKBase";
			AddTargets(new SKBaseTarget(	Platform.win64,
											TargetAPI.Null,
											Optimization.Debug | Optimization.Release,
											BuildType.Full ));
		}

		[Configure()]
		public void ConfigureAll(Configuration conf, SKBaseTarget target)
		{
			conf.Name				= "[target.Api]_[target.Optimization]";
			conf.SolutionFileName	= "[solution.Name]_[target.Build]_[target.Platform]";
			conf.SolutionPath		= SolutionRootPath;

			// Includes: $(SolutionDir)..\..\..\Common_3\Application\ThirdParty\noesisgui\Include;
			// Libs: Xinput9_1_0.lib;ws2_32.lib;gainputstatic.lib;Renderer.lib;OS.lib;%(AdditionalDependencies)

			conf.AddProject< APIProject >( target );

			// The-Forge Projects
			conf.ProjectReferencesByPath.Add(@"[solution.ExternPath]\The-Forge\Examples_3\Unit_Tests\PC Visual Studio 2019\Libraries\OS\OS.vcxproj");
			conf.ProjectReferencesByPath.Add(@"[solution.ExternPath]\The-Forge\Examples_3\Unit_Tests\PC Visual Studio 2019\Libraries\Renderer\Renderer.vcxproj");
			conf.ProjectReferencesByPath.Add(@"[solution.ExternPath]\The-Forge\Examples_3\Unit_Tests\PC Visual Studio 2019\Libraries\Tools\SpirvCross.vcxproj");
			conf.ProjectReferencesByPath.Add(@"[solution.ExternPath]\The-Forge\Common_3\Application\ThirdParty\OpenSource\gainput\Win64\lib\gainputstatic.vcxproj");

			if ( target.Build == BuildType.Full || target.Build == BuildType.Editor )
			{
				conf.AddProject< EmptyProject  >( target );
				conf.AddProject< TransformsProject  >( target );
				conf.AddProject< UIAppProject  >( target );
			}
		}
	}

	public class Main
	{
		[Sharpmake.Main]
		public static void SharpmakeMain(Sharpmake.Arguments arguments)
		{
			Sharpmake.KitsRootPaths.SetUseKitsRootForDevEnv(DevEnv.vs2019, KitsRootEnum.KitsRoot10, Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);

			arguments.Generate<SKBaseSolution>();
		}
	}
}
