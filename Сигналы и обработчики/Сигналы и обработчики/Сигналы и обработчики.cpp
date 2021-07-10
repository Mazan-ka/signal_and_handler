#include "cl_application.h"

int main()
{
	cl_application ob_cl_application(nullptr); //объявление объекта класса cl_application
	ob_cl_application.buildTree(); //вызов метода конструирования дерева иерархии
	return ob_cl_application.launch(); //возврат результата работы метода запуска приложения
}

//Пример ввода:
/*root
root ob_1 1 1
root ob_2 2 1
ob_2 ob_3 3 1
ob_2 ob_4 1 1
ob_4 ob_5 3 1
endtree
1 root ob_5
2 root ob_2
4 ob_1 ob_5
0
root message
ob_1 qwerty
endsignals*/

//Пример вывода:
/*Object tree
root
    ob_1
	ob_2
	    ob_3
	    ob_4
	        ob_5
Set connects
1 root ob_5
2 root ob_2
4 ob_1 ob_5
Emit signals
Signal to ob_5 Text: ob_5->message
Signal to ob_2 Text: ob_2->message
Signal to ob_5 Text: ob_5->qwerty*/