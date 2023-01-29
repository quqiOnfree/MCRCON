#include <Python.h>
#include <iostream>

#include "pythonmodule.h"

namespace PythonModule
{
	void pythonInit()
	{
		Py_Initialize();
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('./Plugin')");
		std::cout << "正在启动无GUI界面...\n";
		std::cout << "hi\n";
		system("pause");
		Py_Finalize();
	}
}
