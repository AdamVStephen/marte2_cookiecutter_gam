/**
 * @file {{cookiecutter.gam_name}}Test.cpp
 * @brief Source file for class {{cookiecutter.gam_name}}Test
 * @date {{cookiecutter.date}}
 * @author {{cookiecutter.author}}
 */
{{cookiecutter.copyright}}

{{cookiecutter.implementation_details}}

#define DLL_API

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "AdvancedErrorManagement.h"
#include "ConfigurationDatabase.h"
#include "ErrorInformation.h"
#include "ErrorManagement.h"
#include "FastMath.h"
#include "GAM.h"
#include "GlobalObjectsDatabase.h"
#include "ObjectRegistryDatabase.h"
#include "RealTimeApplication.h"
#include "StandardParser.h"
#include "{{cookiecutter.gam_name}}.h"
#include "{{cookiecutter.gam_name}}Test.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

class {{cookiecutter.gam_name}}Helper: public MARTe::{{cookiecutter.gam_name}} {
public:
    CLASS_REGISTER_DECLARATION()

    {{cookiecutter.gam_name}}Helper() : MARTe::{{cookiecutter.gam_name}}() {};
    virtual ~{{cookiecutter.gam_name}}Helper() {};
    template <typename Type> bool GetOutput (MARTe::uint32 index, Type& value, MARTe::uint32 offset = 0u);
};

template<typename Type> bool {{cookiecutter.gam_name}}Helper::GetOutput(MARTe::uint32 signalIndex, Type& value, MARTe::uint32 index) {

    using namespace MARTe;

    bool ret = (GetNumberOfOutputSignals() > signalIndex);

    if (!ret) {
        REPORT_ERROR_PARAMETERS(ErrorManagement::InitialisationError, "GetNumberOfOutputSignals() <= %u", signalIndex);
    }

    StreamString signalName;

    if (ret) {
        ret = GetSignalName(OutputSignals, signalIndex, signalName);
    }

    TypeDescriptor signalType = InvalidType;

    if (ret) {
        signalType = GetSignalType(OutputSignals, signalIndex);
        ret = (signalType != InvalidType);
    }

    /* Should test the signal type */

    if (ret) {
        Type* ref = static_cast<Type*>(GetOutputSignalMemory(signalIndex));
        value = ref[index];
        //ret = MemoryOperationsHelper::Copy(&value, static_cast<void*>(static_cast<Type*>(GetOutputSignalMemory(signalIndex)) + offset), sizeof(Type));
    }

    if (ret) {
        REPORT_ERROR_PARAMETERS(ErrorManagement::Information, "{{cookiecutter.gam_name}}Helper::GetOutput - '%s' at offset '%u' '%!'", signalName.Buffer(), index, value);
    }

    return ret;
}


CLASS_REGISTER({{cookiecutter.gam_name}}Helper, "1.0")

/**
 * Starts a MARTe application that uses this driver instance.
 */

namespace {{cookiecutter.gam_name}}TestHelper {

bool ConfigureApplication(const MARTe::char8 * const config) {

    using namespace MARTe;

    ConfigurationDatabase cdb;
    StreamString configStream = config;
    StreamString err;
    configStream.Seek(0);
    StandardParser parser(configStream, cdb, &err);

    ObjectRegistryDatabase *god = ObjectRegistryDatabase::Instance();

    bool ok = parser.Parse();

    if (ok) {
        god->Purge();
        ok = god->Initialise(cdb);
    }
    else {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "StandardParser::Parse failed");
    }

    ReferenceT<RealTimeApplication> application;

    if (ok) {
        application = god->Find("Test");
        ok = application.IsValid();
    }

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::IsValid failed");
    }
    else {
        ok = application->ConfigureApplication();
    }

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::ConfigureApplication failed");
    }

    return ok;

}

static inline bool StartApplication(const MARTe::char8 * const state = "Running") {

    using namespace MARTe;

    ObjectRegistryDatabase *god = ObjectRegistryDatabase::Instance();
    ReferenceT<RealTimeApplication> application = god->Find("Test");

    bool ok = application.IsValid();

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::IsValid failed");
    }
    else {
        ok = application->PrepareNextState(state);
    }

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::PrepareNextState failed");
    }
    else {
        ok = application->StartNextStateExecution();
    }

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::StartNextStateExecution failed");
    }
    return ok;

}

static inline bool StopApplication() {

    using namespace MARTe;

    ObjectRegistryDatabase *god = ObjectRegistryDatabase::Instance();
    ReferenceT<RealTimeApplication> application = god->Find("Test");

    bool ok = application.IsValid();

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::IsValid failed");
    }
    else {
        ok = application->StopCurrentStateExecution();
    }

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::StopCurrentStateExecution failed");
    }

    god->Purge();

    return ok;

}

} /* namespace {{cookiecutter.gam_name}}TestHelper */

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

{{cookiecutter.gam_name}}Test::{{cookiecutter.gam_name}}Test() {
}

{{cookiecutter.gam_name}}Test::~{{cookiecutter.gam_name}}Test() {
}

bool {{cookiecutter.gam_name}}Test::TestConstructor() {
    using namespace MARTe;
    {{cookiecutter.gam_name}} gam;

    bool ok = (gam.GetNumberOfInputSignals() == 0u) && (gam.GetNumberOfOutputSignals() == 0u);

    return ok;
}

bool {{cookiecutter.gam_name}}Test::TestExecute() {
    using namespace MARTe;
    {{cookiecutter.gam_name}} gam;

    bool ok = gam.Execute();

    return ok;
}

bool {{cookiecutter.gam_name}}Test::TestSetup() {
    const MARTe::char8 * const config = ""
      "$Test = {"
      "    Class = RealTimeApplication"
      "    +Functions = {"
      "        Class = ReferenceContainer"
      "        +{{cookiecutter.gam_name}} = {"
      "            Class = {{cookiecutter.gam_name}}"
      "            Gain = 2"
      "            InputSignals = {"
      "                Signal1 = {"
      "                    DataSource = DDB"
      "                    Type = float64"
      "                }"
      "            }"
      "            OutputSignals = {"
      "                Signal1 = {"
      "                    DataSource = DDB"
      "                    Type = float64"
      "                }"
      "            }"
      "        }"
      "    }"
      "    +Data = {"
      "        Class = ReferenceContainer"
      "        DefaultDataSource = DDB"
      "        +DDB = {"
      "            Class = GAMDataSource"
      "        }"
      "        +Timings = {"
      "            Class = TimingDataSource"
      "        }"
      "    }"
      "    +States = {"
      "        Class = ReferenceContainer"
      "        +Running = {"
      "            Class = RealTimeState"
      "            +Threads = {"
      "                Class = ReferenceContainer"
      "                +Thread = {"
      "                    Class = RealTimeThread"
      "                    Functions = { {{cookiecutter.gam_name}} }"
      "                }"
      "            }"
      "        }"
      "    }"
      "    +Scheduler = {"
      "        Class = GAMScheduler"
      "        TimingDataSource = Timings"
      "    }"
      "}";
    
    bool ok = {{cookiecutter.gam_name}}TestHelper::ConfigureApplication(config);

    using namespace MARTe;
    
    ObjectRegistryDatabase *god = ObjectRegistryDatabase::Instance();
    ReferenceT<RealTimeApplication> application = god->Find("Test");
    ReferenceT<{{cookiecutter.gam_name}}> gam = application->Find("Functions.{{cookiecutter.gam_name}}");

    if (ok) {
        ok = gam.IsValid();
    }

    return ok;
}

