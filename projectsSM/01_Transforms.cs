using Sharpmake;

[module: Sharpmake.Include("common.cs")]

namespace SKBase
{
	[Sharpmake.Generate]
	public class TransformsProject : CommonProject
	{
		public TransformsProject()
		{
			Name			= "01_Transforms";
			SourceRootPath	= RootPath + @"\src\01_Transforms";
		}

		[Configure()]
		public void Configure(Configuration conf, SKBaseTarget target)
		{
			conf.Output = Configuration.OutputType.Exe;
			conf.SolutionFolder = "Apps";

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

			// TODO change for only if the file didn't exists
			conf.EventPostBuild.Add("xcopy $(SolutionDir)$(Platform)\\[target.Optimization]\\OS [conf.VcxprojUserFile.LocalDebuggerWorkingDirectory] /E /H /C /I /Y");
		}

		public static void GenerateFiles()
		{}
	}
}
