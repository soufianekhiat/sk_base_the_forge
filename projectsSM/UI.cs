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

            conf.PrecompHeader = $"{Name}/{Name}_pch.h";
            conf.PrecompSource = $"{Name}/{Name}_pch.cpp";
		}

		public static void GenerateFiles()
		{}
	}
}
