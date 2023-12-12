using Sharpmake;

[module: Sharpmake.Include("common.cs")]

[module: Sharpmake.Include("API.cs")]

[module: Sharpmake.Include("UI.cs")]

namespace SKBase
{
	[Sharpmake.Generate]
	public class SKBaseSolution : CommonSolution
	{
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

			// L0 (used for pipeline too)
			conf.AddProject< APIProject >( target );

			if ( target.Build == BuildType.Full || target.Build == BuildType.Editor )
			{
				conf.AddProject< UIProject  >( target );
			}
		}
	}

	public class Main
	{
		[Sharpmake.Main]
		public static void SharpmakeMain(Sharpmake.Arguments arguments)
		{
			Sharpmake.KitsRootPaths.SetUseKitsRootForDevEnv(DevEnv.vs2022, KitsRootEnum.KitsRoot10, Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);

			arguments.Generate<SKBaseSolution>();
		}
	}
}
