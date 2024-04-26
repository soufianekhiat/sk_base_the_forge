using Sharpmake;

[module: Sharpmake.Include("common.cs")]

namespace SKBase
{
	[Sharpmake.Generate]
	public class UIProject : CommonProject
	{
		public UIProject()
		{
			Name			= "UI";
			SourceRootPath	= RootPath + @"\src\UI";
		}

		[Configure()]
		public void Configure(Configuration conf, SKBaseTarget target)
		{
			conf.Output = Configuration.OutputType.Exe;
			conf.SolutionFolder = "UI";

			conf.AddPublicDependency< APIProject >( target );

			conf.VcxprojUserFile = new Configuration.VcxprojUserFileSettings();
			conf.VcxprojUserFile.LocalDebuggerWorkingDirectory = @"$(SolutionDir)WorkingDir";

			conf.IncludePaths.Add(@"[project.ExternPath]/The-Forge/Common_3/");

            conf.PrecompHeader = $"{Name}/{Name}_pch.h";
            conf.PrecompSource = $"{Name}/{Name}_pch.cpp";

			conf.LibraryFiles.Add("$(SolutionDir)$(Platform)/[target.Optimization]/Renderer");
			conf.LibraryFiles.Add("$(SolutionDir)$(Platform)/[target.Optimization]/OS");
			conf.LibraryFiles.Add("$(SolutionDir)$(Platform)/[target.Optimization]/gainputstatic");
			if (target.Platform == Platform.win64)
			{
				conf.LibraryFiles.Add("Xinput9_1_0");
				conf.LibraryFiles.Add("ws2_32");
			}

			// Copy all compiled shader on the working directory
			//xcopy <source path>\*.pdf <destination path> /
			//xcopy C:\git\sk_base_the_forge\x64\Debug\OS C:\git\sk_base_the_forge\WorkingDir /E /H /C /I
			conf.EventPostBuild.Add("xcopy $(SolutionDir)$(Platform)\\[target.Optimization]\\OS [conf.VcxprojUserFile.LocalDebuggerWorkingDirectory] /E /H /C /I /Y");
		}

		public static void GenerateFiles()
		{}
	}
}
