/*
 *  Analyzes files parser.
 *
 *  This implementation uses C++ style.
 *
 *  Copyright (C) Zalogix, 2013
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution.
 *
 *  Ver. 0.1
 */

//#define VS_EXPRESS_2010
#define QT_CREATOR

#ifdef VS_EXPRESS_2010
#include "stdafx.h"
#endif

/*
 * Стандартная библиотека С++
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

/*
 * Стандартная библиотека С
 * разбор строки, с разделителями
 */
#include <string.h>

/*
 * Пространство имен для функций из библиотеки С++
 */
using namespace std;


#ifdef VS_EXPRESS_2010
int _tmain(int argc, _TCHAR* argv[]) {
#else
int  main(int argc, char* argv[]) {
#endif
  /*
   * Разбор параметров программы
   */
  if ( argc <= 1) {
    cout << "Incorrect params!";
    return 0;
  }

  /*
   * Открытие фаила с данными, чтение их
   * в массив строк и закрытие фаила.
   */
  ifstream input_file( argv[1] );
  if ( !input_file ) {
    cout << "Cannot open file.\n";
    return 1;
  }

  vector<string> arr;
  string in_str;

   while( getline( input_file, in_str, '\r' ) ) {
    arr.push_back( in_str );
   }

  input_file.close();


  /*
   * Вывод фаила с данными на экран
   */
  vector<string>::iterator it;

//  cout << " file dump " << endl;

//  for ( it = arr.begin(); it != arr.end(); ++it ) {
//    cout << *it << endl;
//  }

//  cout << " end file dump " << endl;

  /*
   * Проход по всему массиву. Поиск назавание теста по признаку /
   * вторым символом. Рассчет площади амплитуд и вывод на экран результат.
   */
  cout << " start calculate square " << endl;

  const char* is_analyz_name;

  bool is_sqr_calclulated_mode_on = false;
  double sum = 0;
  int    count = 0;
  for ( it = arr.begin(); it != arr.end(); ++it ) {
    string str = *it;
    is_analyz_name = 0;
    is_analyz_name =  find( &str[0], &str[3], '/' );

    /* начало нового анализа, режим рассчета площади включен */
    if ( ( *is_analyz_name == '/' ) && ( is_sqr_calclulated_mode_on ) ) {
      is_sqr_calclulated_mode_on = true;
      cout << "square: "<< (sum / count) << endl;
      sum = 0;
      count = 0;
      cout << "Analyz name: "<< str << endl;
      continue;
    }

    /* начало нового анализа, режим рассчета площади не включен */
    if ( ( *is_analyz_name == '/' ) && ( !is_sqr_calclulated_mode_on ) ) {
      is_sqr_calclulated_mode_on = true;
      sum = 0;
      count = 0;
      cout << "Analyz name: "<< str << endl;
      continue;
    }

    /* не начало нового анализа, режим рассчета площади включен */
    if ( ( *is_analyz_name != '/' ) && ( is_sqr_calclulated_mode_on ) ) {

      if ( str == "" ) {
       // cout << "empty string!" << endl;
        continue;
      }
      /**
       * Целевой код
       */
        char * pch;
        vector<string> tmp_str;
        pch = strtok( (char *)str.c_str(), "\t" );
        while ( pch != NULL ) {
          tmp_str.push_back( pch );
          pch = strtok (NULL, "\t");
        }

        string tst = tmp_str.at(1);
        string st = tst.substr( 0, tst.size() / 2 );

        sum += atof(st.c_str());
        count++;

      continue;
    }

    /* не начало нового анализа, режим рассчета площади не включен */
    if ( ( *is_analyz_name != '/' ) && ( !is_sqr_calclulated_mode_on ) ) {
      cout << "warning" << endl;
      continue;
    }

  }

  return 0;
}
