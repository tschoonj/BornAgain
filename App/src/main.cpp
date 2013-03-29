// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/main.cpp 
//! @brief     Universal test program
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "FunctionalTestFactory.h"
#include "DrawHelper.h"
#include "ProgramOptions.h"
#include "AppOptionsDescription.h"
#include "CoreOptionsDescription.h"
#include "Version.h"
#include "MessageService.h"
#include "Utils.h"

#include <iostream>
#include <string>
#include "TROOT.h"
#include "TApplication.h"

//! Universal test program.

int main(int argc, char **argv)
{
    Utils::EnableFloatingPointExceptions();

    std::cout << AppVersion::g_app_name << " "
              << AppVersion::g_app_version_number << std::endl;

    ProgramOptions command_line_options;
    AddApplicationOptions(&command_line_options);
    AddCoreOptions(&command_line_options);
    command_line_options.parseCommandLine(argc, argv);

    if(command_line_options.getVariables().count("msglog"))
        MSG::SetLevel(command_line_options["msglog"].as<std::string>());

    // set graphics environment
    TApplication *theApp(0);
    if( command_line_options.find("batch") ) {
        (void)theApp;
        gROOT->SetBatch(true);
    } else {
        theApp = new TApplication("theApp", 0, 0);
        DrawHelper::SetStyle();
    }

    // run functional tests
    if( command_line_options.find("all") ) {
        // run all registered tests
        FunctionalTestFactory::execute_all(&command_line_options);

    } else {
        // loop over functional tests,
        // run test if its name is present in command line
        FunctionalTestFactory::iterator it = FunctionalTestFactory::begin();
        for(; it!= FunctionalTestFactory::end(); ++it) {
            if( command_line_options.find( (*it).first ) )
                FunctionalTestFactory::execute(
                    (*it).first,& command_line_options );
        }
    }

    // save report in pdf and root
    if( command_line_options.find("report") ) {
        DrawHelper::saveReport();
    }

    // exit now if there is unrecognized options or plead for help
    if( !command_line_options.isConsistent() ) return 0;

    // hold graphics if it exists
    if( theApp ) {
        std::cout
            << "main() -> Info. Holding graphics, press ctrl-C to exit..."
            << std::endl;
        theApp->Run();
    }

    return 0;
}

