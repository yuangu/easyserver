#ifndef __PROFILER_H__
#define __PROFILER_H__

#include <stack>
#include "misc/Singleton.h"

namespace easygame {

#define OPEN_PF


	// 函数性能分析，使用统一的超时时间
#ifdef OPEN_PF
#define FUNC_PF(log) easygame::FuncProfiler pf(log, 0);
#else
#define FUNC_PF(log)
#endif

	// 函数性能分析，使用指定的超时时间
#ifdef OPEN_PF
#define FUNC_PF_EXT(log, time)	easygame::FuncProfiler pf(log, time);
#else
#define FUNC_PF_EXT(log, time)
#endif



#ifdef OPEN_PF
#define CODE_PF_BEGIN()		easygame::Profiler::getInstance().begin();
#define CODE_PF_END(log)	easygame::Profiler::getInstance().end(log);
#else
#define CODE_PF_BEGIN()
#define CODE_PF_END(log)
#endif


	/************************************************************************/
	/* 函数性能分析类（精确到微妙）                                                                     */
	/************************************************************************/
	class FuncProfiler
	{
	public:
		//FuncProfiler(const char* log, double timeout = 0);
		FuncProfiler(const char* log, int64 timeout = 0);
		virtual ~FuncProfiler();

	private:
		string m_strLog;
		//double m_timeout;
		//LARGE_INTEGER m_feq;
		//LARGE_INTEGER m_lastTick;
		int64 m_timeout;
		int64 m_lastTick;
	};




	/************************************************************************/
	/* 代码段性能分析类（精确到微妙）                                                                     */
	/************************************************************************/
	struct stPF
	{
		//LARGE_INTEGER lastTick;
		int64 lastTick;
	};

	class Profiler : public Singleton<Profiler>
	{
	public:
		Profiler(void);
		virtual ~Profiler(void);

		/**
		* @brief	记录开始时间
		* @param	
		* @return	
		*/
		void begin();

		/**
		* @brief	计算消耗时间
		* @param	log	日志说明
		* @param	timeout 超时时间,默认是立即输出，不判断超时
		* @return	
		*/
		//void end(const char* log, double timeout = 0);
		void end(const char* log, int64 timeout = 0);

		/**
		* @brief	开启日志输出
		* @param	
		* @return	
		*/
		void openLog() { m_isLogOpened = true; }

		/**
		* @brief	关闭日志输出
		* @param	
		* @return	
		*/
		void closeLog() { m_isLogOpened = false; }

		/**
		* @brief	判断是日志输出是否开启
		* @param	
		* @return	
		*/
		bool isLogOpened() { return m_isLogOpened; }

		/**
		* @brief	设置超时时间
		* @param	
		* @return	
		*/
		//void setTimeout(double timeout) { m_timeout = timeout; }
		void setTimeout(int64 timeout) { m_timeout = timeout; }

		/**
		* @brief	取得超时时间
		* @param	
		* @return	
		*/
		//double getTimeout() { return m_timeout; }
		int64 getTimeout() { return m_timeout; }

	private:
		bool m_isLogOpened;
		int64 m_timeout;
		int64 m_lastTick;
		//double m_timeout;
		//LARGE_INTEGER m_feq;
		std::stack<stPF> m_fpItems;
	};


}	// namespace

#endif