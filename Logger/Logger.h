#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <string>
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>

namespace qlog
{
	enum class LogDataType
	{
		LINFO,
		LWARNING,
		LERROR
	};

	struct LogData
	{
		LogDataType		dataType;
		std::string		data;
		time_t			time;
	};

	class Logger
	{
	public:
		Logger()
		{
			std::filesystem::create_directory("./logs");

			time_t time_seconds = std::time(nullptr);
			tm t_tm;
			localtime_s(&t_tm, &time_seconds);
			char formatTime[64] = { 0 };
			std::snprintf(formatTime, 64, "%04d-%02d-%02d-%02d-%02d-%02d",
				t_tm.tm_year + 1900,
				t_tm.tm_mon + 1,
				t_tm.tm_mday,
				t_tm.tm_hour,
				t_tm.tm_min,
				t_tm.tm_sec);

			if (std::filesystem::exists("./logs/" + std::string(formatTime) + ".log"))
			{
				m_inFile.open("./logs/" + std::string(formatTime) + ".log", std::ios::ios_base::app);
			}
			else
			{
				m_inFile.open("./logs/" + std::string(formatTime) + ".log");
			}

			m_isRunning = true;
			m_isChanging = false;

			m_thread = std::thread([this]() {
			while (true)
			{
				if (!m_queue.empty())
				{
					m_isChanging = true;
					LogData data = std::move(m_queue.front());
					m_queue.pop();
					m_isChanging = false;

					std::string outString;

					{
						tm t_tm;
						localtime_s(&t_tm, &data.time);
						char formatTime[64] = { 0 };
						std::snprintf(formatTime, 64, "%04d-%02d-%02d %02d:%02d:%02d",
							t_tm.tm_year + 1900,
							t_tm.tm_mon + 1,
							t_tm.tm_mday,
							t_tm.tm_hour,
							t_tm.tm_min,
							t_tm.tm_sec);

						outString += '[' + std::string(formatTime) + ']';
					}

					switch (data.dataType)
					{
					case LogDataType::LINFO:
						outString += "[INFO]";
						break;
					case LogDataType::LWARNING:
						outString += "[WARNING]";
						break;
					case LogDataType::LERROR:
						outString += "[ERROR]";
						break;
					}

					outString += data.data + '\n';

					std::cout << outString;
					m_inFile << outString;
					m_inFile.flush();

					continue;
				}
				else
				{
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}
				if (!m_isRunning) return;
			}
				});
		}

		void info(const std::string& data)
		{
			pushData(LogDataType::LINFO, data);
		}

		void warning(const std::string& data)
		{
			pushData(LogDataType::LWARNING, data);
		}

		void error(const std::string& data)
		{
			pushData(LogDataType::LERROR, data);
		}

		~Logger()
		{
			m_isRunning = false;
			m_thread.join();
		}
	protected:
		void pushData(LogDataType type, const std::string& data)
		{
			while (!m_isChanging)
			{
				m_isChanging = true;
				m_queue.push(LogData({ type, std::string(data), std::time(nullptr) }));
				m_isChanging = false;
				break;
			}
		}
	private:
		std::ofstream		m_inFile;
		std::queue<LogData>	m_queue;
		std::thread			m_thread;
		std::mutex			m_mutex;
		std::atomic_bool	m_isRunning;
		std::atomic_bool	m_isChanging;
	};
}
