/**
 * @file {{cookiecutter.gam_name}}.cpp
 * @brief Source file for class {{cookiecutter.gam_name}}
 * @date {{cookiecutter.date}}
 * @author {{cookiecutter.author}}
 */

{{cookiecutter.copyright}}

{{cookiecutter.implementation_details}}

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "AdvancedErrorManagement.h"
#include "CLASSMETHODREGISTER.h"
#include "RegisteredMethodsMessageFilter.h"
#include "{{cookiecutter.gam_name}}.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

namespace MARTe {

{{cookiecutter.gam_name}}::{{cookiecutter.gam_name}}() :
        GAM(), MessageI() {

}

{{cookiecutter.gam_name}}::~{{cookiecutter.gam_name}}() {

}

bool {{cookiecutter.gam_name}}::Setup() {

    bool ret = (GetNumberOfInputSignals() == 0u);

    if (!ret) {
        REPORT_ERROR(ErrorManagement::InitialisationError, "GetNumberOfInputSignals() != 0u");
    }

    uint32 signalIndex;

    for (signalIndex = 0u; (signalIndex < GetNumberOfOutputSignals()) && (ret); signalIndex++) {

        StreamString signalName;

        ret = GetSignalName(OutputSignals, signalIndex, signalName);

        uint32 signalByteSize = 0u;

        if (ret) {
            ret = GetSignalByteSize(OutputSignals, signalIndex, signalByteSize);
        }

        TypeDescriptor signalType = InvalidType;

        if (ret) {
            signalType = GetSignalType(OutputSignals, signalIndex);
            ret = (signalType != InvalidType);
        }

        StreamString signalTypeName = TypeDescriptor::GetTypeNameFromTypeDescriptor(signalType);

        if (ret) {
            REPORT_ERROR(ErrorManagement::Information, "Signal '%!' has type '%!'", signalName.Buffer(), signalTypeName.Buffer());
        }

        if (ret) {
            ret = MoveToSignalIndex(OutputSignals, signalIndex);
        }

        AnyType signalDefType = configuredDatabase.GetType("Default");
        AnyType signalDefValue(signalType, 0u, GetOutputSignalMemory(signalIndex));

        uint32 signalNumberOfDimensions = 0u;
        if (ret) {
            //Ugly hack to solve the fact that GetSignalNumberOfElements does not support matrices...
            if (signalDefType.GetNumberOfDimensions() > 1u) {
                signalNumberOfDimensions = signalDefType.GetNumberOfDimensions();
            }
            else {
                ret = GetSignalNumberOfDimensions(OutputSignals, signalIndex, signalNumberOfDimensions);
            }
        }
        if (ret) {
            signalDefValue.SetNumberOfDimensions(static_cast<uint8>(signalNumberOfDimensions));
        }
        uint32 signalNumberOfElements = 0u;
        if (ret) {
            if (signalNumberOfDimensions == 2u) {
                uint8 dimensionIndex;
                for (dimensionIndex = 0u; ((dimensionIndex < signalNumberOfDimensions) && (ret)); dimensionIndex++) {
                    uint32 dimensionNumberOfElements = signalDefType.GetNumberOfElements(static_cast<uint32>(dimensionIndex));
                    signalDefValue.SetNumberOfElements(static_cast<uint32>(dimensionIndex), dimensionNumberOfElements);
                }
            }
            else {
                ret = GetSignalNumberOfElements(OutputSignals, signalIndex, signalNumberOfElements);
                if (signalNumberOfElements > 1u) {
                    signalNumberOfDimensions = 1u;
                }
                if (ret) {
                    if (signalNumberOfDimensions > 0u) {
                        signalDefValue.SetNumberOfElements(0u, signalNumberOfElements);
                    }
                }
            }
        }
        if (ret) {
            ret = MoveToSignalIndex(OutputSignals, signalIndex);
        }

        if (ret) {
            ret = configuredDatabase.Read("Default", signalDefValue);
        }

        if (ret) {
            REPORT_ERROR(ErrorManagement::Information, "Signal '%!' has value '%!'", signalName.Buffer(), signalDefValue);
        }
        else {
            REPORT_ERROR(ErrorManagement::InitialisationError, "{{cookiecutter.gam_name}}::Setup - GetSignalDefaultValue '%s'", signalName.Buffer());
        }

    }

    // Install message filter
    ReferenceT<RegisteredMethodsMessageFilter> registeredMethodsMessageFilter("RegisteredMethodsMessageFilter");

    if (ret) {
        ret = registeredMethodsMessageFilter.IsValid();
    }

    if (ret) {
        registeredMethodsMessageFilter->SetDestination(this);
        ret = InstallMessageFilter(registeredMethodsMessageFilter);
    }

    return ret;
}

bool {{cookiecutter.gam_name}}::Execute() {
    return true;
}

ErrorManagement::ErrorType {{cookiecutter.gam_name}}::SetOutput(ReferenceContainer& message) {

    ErrorManagement::ErrorType ret = ErrorManagement::NoError;

    // Assume one ReferenceT<StructuredDataI> contained in the message

    bool ok = (message.Size() == 1u);
    ReferenceT<StructuredDataI> data = message.Get(0u);

    if (ok) {
        ok = data.IsValid();
    }

    if (!ok) {
        ret = ErrorManagement::ParametersError;
        REPORT_ERROR(ret, "Message does not contain a ReferenceT<StructuredDataI>");
    }

    StreamString signalName;
    uint32 signalIndex = 0u;

    if (ok) {
        if (data->Read("SignalName", signalName)) {
            ok = GetSignalIndex(OutputSignals, signalIndex, signalName.Buffer());
        }
        else {
            ok = data->Read("SignalIndex", signalIndex);
        }
    }

    if (ok) {
        ok = (signalIndex < GetNumberOfOutputSignals());
    }

    if (!ok) {
        ret = ErrorManagement::ParametersError;
        REPORT_ERROR(ret, "No valid signal name or index provided");
    }

    TypeDescriptor signalType = InvalidType;

    if (ok) {
        signalType = GetSignalType(OutputSignals, signalIndex);
        ok = (signalType != InvalidType);
    }

    if (ok) {

        // Signal index and type are tested and valid ... go ahead with AnyType instantiation

        // Use the default value type to query the signal properties (dimensions, ...)
        /*lint -e{534}  [MISRA C++ Rule 0-1-7], [MISRA C++ Rule 0-3-2]. Justification: SignalIndex is tested valid prio to this part of the code.*/
        MoveToSignalIndex(OutputSignals, signalIndex);
        AnyType signalDefType = configuredDatabase.GetType("Default");
        AnyType signalNewValue(signalType, 0u, GetOutputSignalMemory(signalIndex));

        uint8 signalNumberOfDimensions = signalDefType.GetNumberOfDimensions();
        signalNewValue.SetNumberOfDimensions(signalNumberOfDimensions);

        uint32 dimensionIndex;

        for (dimensionIndex = 0u; dimensionIndex < signalNumberOfDimensions; dimensionIndex++) {
            uint32 dimensionNumberOfElements = signalDefType.GetNumberOfElements(static_cast<uint32>(dimensionIndex));
            signalNewValue.SetNumberOfElements(static_cast<uint32>(dimensionIndex), dimensionNumberOfElements);
        }

        if (data->Read("SignalValue", signalNewValue)) {
            REPORT_ERROR(ErrorManagement::Information, "Signal '%!' new value '%!'", signalName.Buffer(), signalNewValue);
        }
        else {
            ret = ErrorManagement::ParametersError;
            REPORT_ERROR(ret, "Failed to read and apply new signal value");
        }

    }

    return ret;
}

CLASS_REGISTER({{cookiecutter.gam_name}}, "1.0")

/*lint -e{1023} Justification: Macro provided by the Core.*/
CLASS_METHOD_REGISTER({{cookiecutter.gam_name}}, SetOutput)

} /* namespace MARTe */

