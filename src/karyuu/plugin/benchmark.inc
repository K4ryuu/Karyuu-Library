#if defined _KARYUU_MODULE_BENCHMARK_INCLUDED_
	#endinput
#endif
#define _KARYUU_MODULE_BENCHMARK_INCLUDED_

#include <profiler>

bool g_bIsStarted;
int g_iRepeats;
ArrayList g_hFunctionsNames;
ArrayList g_hTestsTotalResult;

stock void Karyuu_Benchmark_Initialize(int iRepeat = 100)
{
	if(g_bIsStarted)
		ThrowError("Benchmark session is running!");

	g_iRepeats = iRepeat;
	g_bIsStarted = true;
	g_hFunctionsNames = new ArrayList(256);
	g_hTestsTotalResult = new ArrayList();

	PrintToServer(" ");
	PrintToServer("[ToolKitsune] A benchmark session has started.");
}

stock void Karyuu_Benchmark_TestFunction(Function testFunction, char[] sFunctionName)
{
	if(!g_bIsStarted)
		ThrowError("Benchmark session is not running!");

	if(testFunction == INVALID_FUNCTION)
		ThrowError("Invalid function! '%s'", sFunctionName);

	if(g_hFunctionsNames.FindString(sFunctionName) != -1)
		ThrowError("Function already registered! '%s'", sFunctionName);

	g_hFunctionsNames.PushString(sFunctionName);

	PrintToServer("[ToolKitsune] Benchmarking function: %s", sFunctionName);

	Profiler prof = new Profiler();

	prof.Start();

	for(int num; num < g_iRepeats; num++)
	{
		Call_StartFunction(INVALID_HANDLE, testFunction);
		Call_Finish();
	}

	prof.Stop();

	g_hTestsTotalResult.Push(prof.Time);

	delete prof;
}

stock void Karyuu_Benchmark_Results()
{
	if(!g_bIsStarted)
		ThrowError("Benchmark session is not running!");

	char buffer[23];
	float best_time = 1.0, lost_time, time;
	int best_place, lost_place;

	for(int id; id < g_hFunctionsNames.Length; id++)
	{
		time = g_hTestsTotalResult.Get(id);

		if(time < best_time)
		{
			best_time = time;
			best_place = id;
		}

		if(time > lost_time)
		{
			lost_time = time;
			lost_place = id;
		}
	}

	PrintToServer(" ");
	PrintToServer("[ToolKitsune] Result with %i tests:", g_iRepeats);
	PrintToServer("[ToolKitsune]         Function name       | Total, sec |   Avg, ms   |  Speed   | Performance");

	for(int id; id < g_hFunctionsNames.Length; id++)
	{
		g_hFunctionsNames.GetString(id, buffer, sizeof(buffer));

		if(buffer[0] == '_')
			Format(buffer, sizeof(buffer), buffer[1]);

		time = g_hTestsTotalResult.Get(id);
		PrintToServer("[ToolKitsune] %28s|  %.6f  | %.9f | x%.4f | %.1f%% %s", buffer, time, (time * 1000 / g_iRepeats), (lost_time / time), (best_time/ time * 100.0),
		id == best_place ? "<<== Fastest" : (id == lost_place ? "<<== Slowest" : ""));
	}

	delete g_hFunctionsNames;
	delete g_hTestsTotalResult;
	g_bIsStarted = false;

	PrintToServer(" ");
}