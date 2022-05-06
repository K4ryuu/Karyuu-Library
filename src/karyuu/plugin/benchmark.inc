#if defined _KARYUU_MODULE_BENCHMARK_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_BENCHMARK_INCLUDED_

#include <profiler>

static bool bBenchmarkState;

stock void	Karyuu_ToggleProfiling()
{
	char sTime[32];

	if (!start)
	{
		delete g_hTimer;

		FormatTime(sTime, sizeof(sTime), "%F_%H-%M-%S", GetTime());
		FormatEx(g_PathProfilerLog, sizeof(g_PathProfilerLog), "%s_%s.log", g_PathPrefix, sTime);

		if (g_bL4D2)
		{
			g_ptrFile = FileSize(g_PathCosole);
		}
		else {
			SetCvarSilent(g_CVarLogFile, g_PathProfilerLog);
		}

		ReplyToCommand(client, "\x04[START]\x05 Profiler is started...");
		ServerCommand("vprof_on");
		ServerExecute();
		RequestFrame(OnFrameDelay);
	}
	else
	{
		ServerCommand("sm prof stop vprof");
		ServerCommand("sm prof dump vprof");
		ServerCommand("vprof_off");
		ReplyToCommand(client, "\x04[STOP]\x05 Saving profiler log to: %s", g_PathProfilerLog);

		// Profiler needs some time for analysis
		g_hTimer = CreateTimer(60.0, Timer_RestoreCvar);
	}
	bBenchmarkState = !bBenchmarkState;
}

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

stock Action Timer_RestoreCvar(Handle timer)
{
	SetCvarSilent(g_CVarLogFile, g_PathOrig);
	g_hTimer = null;
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