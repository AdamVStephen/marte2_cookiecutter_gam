/**
 * @file {{cookiecutter.gam_name}}.h
 * @brief Header file for class {{cookiecutter.gam_name}}

 * @date {{cookiecutter.date}}
 * @author {{cookiecutter.author}}
 */

{{cookiecutter.copyright}}

{{cookiecutter.interface_details}}

// COOKIECUTTER TODO : MANAGE THE IDEMPOTENT GUARD GENERATION

#ifndef {{cookiecutter.gam_include_guard}}
#define {{cookiecutter.gam_include_guard}}

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "GAM.h"
#include "MessageI.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {

/**
 * @brief GAM which provides constant output signals. 
 * @details This GAM provides constant output signals, the value of which is defined through configuration, and
 * may be asynchronously altered using MARTe messages sent e.g. from a StateMachine.
 *
 * The configuration syntax is (names and signal quantity are only given as an example):
 *
 * <pre>
 * +Constants = {
 *     Class = {{cookiecutter.gam_name}}
 *     OutputSignals = {
 *         Signal1 = {
 *             DataSource = "DDB"
 *             Type = uint32
 *             Default = 0
 *         }
 *         Signal2 = {
 *             DataSource = "DDB"
 *             Type = int32
 *             Default = 100
 *         }
 *         Signal3 = {
 *             DataSource = "DDB"
 *             Type = int8
 *             NumberOfDimensions = 1
 *             NumberOfElements = 8
 *             Default = {1 2 3 4 5 6 7 8}
 *         }
 *     }
 * }
 * </pre>
 *
 * The GAM registers a messageable 'SetOutput' method which allows to update signals through messages:
 *
 * <pre>
 * +Message = {
 *     Class = Message
 *     Destination = "Functions.Constants"
 *     Function = "SetOutput"
 *     +Parameters = {
 *         Class = ConfigurationDatabase
 *         SignalName = "Signal1" // The name of the signal to modify, or
 *         SignalIndex = 0 // Alternatively, the index of the signal.
 *         SignalValue = 10
 *     }
 * }
 * </pre>
 */
class {{cookiecutter.gam_name}}: public GAM, public MessageI {
public:
    CLASS_REGISTER_DECLARATION()

    /**
     * @brief Constructor. NOOP.
     */
    {{cookiecutter.gam_name}}();

    /**
     * @brief Destructor. NOOP.
     */
    virtual ~{{cookiecutter.gam_name}}();

    /**
     * @brief Initialises the output signal memory with default values provided through configuration.
     * @return true if the pre-conditions are met.
     * @pre
     *   SetConfiguredDatabase() && GetNumberOfInputSignals() == 0 &&
     *   for each signal i: The default value provided corresponds to the expected type and dimensionality.
     */
    virtual bool Setup();

    /**
     * @brief Execute method. NOOP.
     * @return true.
     */
    virtual bool Execute();

    /**
     * @brief SetOutput method.
     * @details The method is registered as a messageable function. It assumes the ReferenceContainer
     * includes a reference to a StructuredDataI instance which contains a valid 'SignalName' attribute, 
     * or alternatively, a valid 'SignalIndex' from which the output signal can be identified. 
     * The 'SignalValue' attribute must match the expected type and dimensionality of the output signal.
     * @return ErrorManagement::NoError if the pre-conditions are met, ErrorManagement::ParametersError
     * otherwise.
     * @pre
     *   'SignalIndex' < GetNumberOfOutputSignals() &&
     *   The 'SignalValue' provided corresponds to the expected type and dimensionality.
     */
    ErrorManagement::ErrorType SetOutput(ReferenceContainer& message);
};

}

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /*  {{cookiecutter.gam_include_guard}} */

