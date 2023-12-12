using Sharpmake;

[module: Sharpmake.Include("common.cs")]

namespace SKBase
{
	[Sharpmake.Generate]
	public class APIProject : CommonProject
	{
		public APIProject()
		{
			Name			= "API";
			SourceRootPath	= RootPath + @"\src\api";
		}

		[Configure()]
		public void Configure(Configuration conf, SKBaseTarget target)
		{
			conf.SolutionFolder = "API";
            conf.PrecompHeader = $"{Name}/{Name}_pch.h";
            conf.PrecompSource = $"{Name}/{Name}_pch.cpp";
		}

		public static void GenerateFiles()
		{}
	}
}
