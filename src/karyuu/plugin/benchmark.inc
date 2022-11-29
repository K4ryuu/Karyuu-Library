#if defined _KARYUU_MODULE_BENCHMARK_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_BENCHMARK_INCLUDED_

#include <profiler>

stock void OnFrameDelay()
{
	ServerCommand("sm prof start vprof");
}

stock void SetCvarSilent(ConVar cvar, char[] value)
{
	int flags = cvar.Flags;
	cvar.Flags &= ~FCVAR_NOTIFY;
	cvar.SetString(value);
	cvar.Flags = flags;
}

stock void Karyuu_Benchmark(Function func, const char[] name, int iterations)
{
	Profiler profile = new Profiler();
	float	 sum, sum2, diff, min, max, avg, stddev;

	for (int i = 0; i < iterations; i++)
	{
		profile.Start();
		Call_StartFunction(INVALID_HANDLE, func);
		Call_Finish();
		profile.Stop();

		diff = profile.Time;

		sum += diff;
		sum2 += diff * diff;

		if (i == 0 || diff < min)
			min = diff;

		if (i == 0 || diff > max)
			max = diff;
	}

	avg	   = sum / float(iterations);
	stddev = SquareRoot(sum2 / float(iterations) - avg * avg);

	LogMessage("%s executed %d times | Results - Fastest: %f, Slowest: %f, Avarage: %f, Standard deviation: %f", name, iterations, min, max, avg, stddev);
	delete profile;
}