/**
 * @file {{cookiecutter.gam_name}}Test.h
 * @brief Header file for class {{cookiecutter.gam_name}}Test
 * @date {{cookiecutter.date}}
 * @author {{cookiecutter.author}}
 */

{{cookiecutter.copyright}}

{{cookiecutter.interface_details}}

// TODO : COOKIECUTTER GENERATE IDEMPOTENT GUARD

#ifndef {{cookiecutter.test_include_guard}}
#define {{cookiecutter.test_include_guard}}

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/
/**
 * @brief Tests the {{cookiecutter.gam_name}} public methods.
 */
class {{cookiecutter.gam_name}}Test {
public:
    /**
     * @brief Constructor. NOOP.
     */
    {{cookiecutter.gam_name}}Test();

    /**
     * @brief Destructor. NOOP.
     */
    virtual ~{{cookiecutter.gam_name}}Test();

    /**
     * @brief Tests the default constructor
     * @return true after GAM instantiation.
     */
    bool TestConstructor();

    /**
     * @brief Tests the Execute() method
     * @return true if Execute succeeds.
     */
    bool TestExecute();

    /**
     * @brief Tests the Setup() method
     * @details Verify the post-conditions
     * @return true if Setup() succeeds.
     */
    bool TestSetup();


};

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* {{cookiecutter.test_include_guard}} */

