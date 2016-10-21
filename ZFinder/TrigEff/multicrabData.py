#!/usr/bin/env python
"""
This is a small script that does the equivalent of multicrab.
"""
import os
from optparse import OptionParser

#from CRABAPI.RawCommand import crabCommand
import CRABAPI
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException


def getOptions():
    """
    Parse and return the arguments provided by the user.
    """
    usage = ("Usage: %prog --crabCmd CMD [--workArea WAD --crabCmdOpts OPTS]"
             "\nThe multicrab command executes 'crab CMD OPTS' for each project directory contained in WAD"
             "\nUse multicrab -h for help")

    parser = OptionParser(usage=usage)

    parser.add_option('-c', '--crabCmd',
                      dest = 'crabCmd',
                      default = '',
                      help = "crab command",
                      metavar = 'CMD')

    parser.add_option('-w', '--workArea',
                      dest = 'workArea',
                      default = '',
                      help = "work area directory (only if CMD != 'submit')",
                      metavar = 'WAD')

    parser.add_option('-o', '--crabCmdOpts',
                      dest = 'crabCmdOpts',
                      default = '',
                      help = "options for crab command CMD",
                      metavar = 'OPTS')

    (options, arguments) = parser.parse_args()

    if arguments:
        parser.error("Found positional argument(s): %s." % (arguments))
    if not options.crabCmd:
        parser.error("(-c CMD, --crabCmd=CMD) option not provided.")
    if options.crabCmd != 'submit':
        if not options.workArea:
            parser.error("(-w WAR, --workArea=WAR) option not provided.")
        if not os.path.isdir(options.workArea):
            parser.error("'%s' is not a valid directory." % (options.workArea))

    return options


def main():

    options = getOptions()

    # The submit command needs special treatment.
    if options.crabCmd == 'submit':

        #--------------------------------------------------------
        # This is the base config:
        #--------------------------------------------------------
        from crab3DataConfFile import config
        #--------------------------------------------------------

        # Will submit one task for each of these input datasets.
        inputDatasets = [
                        # '/SingleElectron/Run2012A-22Jan2013-v1/AOD',
                         #'/SingleElectron/Run2012B-22Jan2013-v1/AOD',
                         #'/SingleElectron/Run2012C-22Jan2013-v1/AOD',
                         '/SingleElectron/Run2012D-22Jan2013-v1/AOD',
                        ]

        for inDS in inputDatasets:
            reload(CRABAPI)
            # inDS is of the form /A/B/C. Since B is unique for each inDS, use this in the CRAB request name.
            config.General.requestName = inDS.split('/')[2]
            config.Data.inputDataset = inDS
            
            #config.Data.outputDatasetTag = '%s_TESTTRESTTEST%s' % (config.General.workArea, config.General.requestName)
            # Submit.
            print 'SANITY CHECKs_ %s TESTTRESTTEST %s' % (config.General.workArea, config.General.requestName)
            try:
                print "Submitting for input dataset %s" % (inDS)
                print "I am going insane %s For real" %(options.crabCmd) 
                CRABAPI.RawCommand.crabCommand(options.crabCmd, config = config,  *options.crabCmdOpts.split())
            except HTTPException as hte:
                print "TESt Submission for input dataset %s failed: %s" % (inDS, hte.headers)
            except ClientException as cle:
                print "TEST Submission for input dataset %s failed: %s" % (inDS, cle)

    # All other commands can be simply executed.
    elif options.workArea:

        for dir in os.listdir(options.workArea):
            projDir = os.path.join(options.workArea, dir)
            if not os.path.isdir(projDir):
                continue
            # Execute the crab command.
            msg = "Executing (the equivalent of): crab %s --dir %s %s" % (options.crabCmd, projDir, options.crabCmdOpts)
            print "-"*len(msg)
            print msg
            print "-"*len(msg)
            try:
                CRABAPI.RawCommand.crabCommand(options.crabCmd, dir = projDir, *options.crabCmdOpts.split())
            except HTTPException as hte:
                print "Failed executing command %s for task %s: %s" % (options.crabCmd, projDir, hte.headers)
            except ClientException as cle:
                print "Failed executing command %s for task %s: %s" % (options.crabCmd, projDir, cle)


if __name__ == '__main__':
    main()
