/**
 * @file {{cookiecutter.gam_name}}GTest.cpp
 * @brief Source file for class {{cookiecutter.gam_name}}GTest
 * @date {{cookiecutter.date}}
 * @author {{cookiecutter.author}}
 */

{{cookiecutter.copyright}}

{{cookiecutter.implementation_details}}

#define DLL_API

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/
#include "gtest/gtest.h"
/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "{{cookiecutter.gam_name}}.h"
#include "{{cookiecutter.gam_name}}Test.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

TEST({{cookiecutter.gam_name}}GTest,TestConstructor) {
    {{cookiecutter.gam_name}}Test test;
    ASSERT_TRUE(test.TestConstructor());
}

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

