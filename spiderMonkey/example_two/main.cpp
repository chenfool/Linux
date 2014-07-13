#define XP_PC

#include <string>
#include <iostream>
#include <fstream>
#include <jsapi.h>

#include "JSCustomer.h"

JSClass globalClass = 
{
  "Global", 0,
  JS_PropertyStub,  JS_PropertyStub,JS_PropertyStub, JS_PropertyStub,
  JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub,  JS_FinalizeStub
};

void main(int argc, char *argv[])
{
	if ( argc < 2 )
	{
		std::cout << "JSExec usage" << std::endl
			      << "------------" << std::endl
				  << "JSExec <fileName>" << std::endl;
	}

	std::string script;
	std::string buffer;
	std::ifstream istr(argv[1]);
	if ( istr.is_open() )
	{
		do
		{
			std::getline(istr, buffer);
			script += buffer;
		} while (!istr.fail());
	}
	else
	{
		std::cout << "JSExec error" << std::endl
			      << "------------" << std::endl
				  << "Can't open scriptfile " << argv[1] << std::endl;
		exit(0);
	}

	JSRuntime *rt = JS_Init(1000000L);

	if ( rt )
	{
		JSContext *cx = JS_NewContext(rt, 8192);
		if ( cx )
		{
		    JSObject *globalObj = JS_NewObject(cx, &globalClass, 0, 0);
			if ( globalObj )
			{
				JS_InitStandardClasses(cx, globalObj);

				// Init JSCustomer
				JSCustomer::JSInit(cx, globalObj);

				// Execute the script
				jsval rval;
				uintN lineno = 0;

				JSString *str;
				JSBool ok = JS_EvaluateScript(cx, globalObj, script.c_str(), script.length(), argv[1], lineno, &rval);
				if ( ok == JS_TRUE )
				{
					str = JS_ValueToString(cx, rval);
					char *s = JS_GetStringBytes(str);
					std::cout << "JSExec result" << std::endl
					          << "-------------" << std::endl
					          << s << std::endl;
				}
				else
				{
					std::cout << "JSExec error" << std::endl
							  << "------------" << std::endl
							  << "Error in JavaScript file " << argv[1] << std::endl;
				}
			}
			else
			{
				std::cout << "Unable to create the global object";
			}
		    JS_DestroyContext(cx);
		}
		else
		{
			std::cout << "Unable to create a context";
		}
	    JS_Finish(rt);
	}
	else
	{
		std::cout << "Unable to initialize the JavaScript Engine";
	}
}

