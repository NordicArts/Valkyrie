#!/bin/bash
oldCC=$CC
oldCXX=$CXX

# Set the compiler to clang
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

usage()
{
cat << EOF
This script can build, clean, and grab new versions,

usage: $0 options

OPTIONS:
    -h  Show this message
    -v  Verbose
    -p  Pull, pulls the latest code and all its gitmodules
    -t  Test Build, once built run the unit tests
    -n  No Clean
EOF
}

# Make the build
makeIt()
{
    beLoud=$1

    if [[ $beLoud == 1 ]]; then
        echo "Make Verbose"

        make
    else
        echo "Make Quiet"

        make >> /dev/null
    fi
}

# Pull the latest stuff
pullCode()
{
    beLoud=$1

    if [[ $beLoud == 1 ]]; then
        echo "Pull Verbose"

        git submodule init
        git submodule update --recursive
        git submodule foreach git pull origin master --recurse-submodules
    else
        echo "Pull Quiet"

        git submodule init >> /dev/null
        git submodule update --recursive >> /dev/null
        git submodule foreach git pull origin master --recurse-submodules >> /dev/null
    fi
}

# Game Library
gameLibrary() 
{
    beLoud=$1
    testIt=$2

    endEcho="GameLib"
    endResult="cmake -C CMakeConfigs/"

    # Test Builds
    if [[ $testIt == 1 ]]; then
        endEcho+=", Test"
        endResult+="TestFull.txt"
    else
        endEcho+=", Non-Test"
        endResult+="Full.txt"
    fi

    endResult+=" ."

    # Verbose
    if [[ $beLoud == 1 ]]; then
        endEcho+=", Verbose"
    else
        endEcho+=", Quiet"
        endResult+=" >> /dev/null"
    fi

    echo $endEcho
    eval $endResult
}

builder()
{

    beLoud=$1
    testIt=$2

    endEcho="ReBuild"
    endResult=""

    # Testing
    if [[ $testIt == 1 ]]; then
        endEcho+=", Test"
        endResult+="cmake -C CMakeConfigs/Test.txt ."
    else
        endEcho+=", Non-Test"
        endResult+="cmake ."
    fi

    # Verbose
    if [[ $beLoud == 1 ]]; then
        endEcho+=", Verbose"
    else
        endEcho+=", Quiet"
        endResult+=" >> /dev/null"
    fi

    echo $endEcho
    eval $endResult

    makeIt $beLoud
}

# Variables
OPT='build'
GENERATE='linux'
VERBOSE=false
TEST=false
PULL=false
MAKER=false
CLEAN=1

# Go through the options
while getopts ":o:g:?phvnt" OPTION; do
    case $OPTION in
        o)
            OPT=$OPTARG
            ;;
        t)
            TEST=1
            ;;
        n)
            CLEAN=false
            ;;
        p)
            PULL=1
            ;;
        h)
            usage
            exit 1
            ;;
        v)
            VERBOSE=1
            ;;
        ?)
            usage
            exit
            ;;
    esac
done

# Clear screen
clear

# Pull
if [[ $PULL == 1 ]]; then
    pullCode $VERBOSE
fi

# Build Standard
if [[ $OPT == "build" ]]; then
    if [[ $CLEAN == 1 ]]; then
        ./cleaner.sh -t build
    fi

    gameLibrary $VERBOSE $TEST

    if [[ $CLEAN == 1 ]]; then
        ./cleaner.sh -t cmake
    fi
fi

# Run the tests if its supposed to
if [[ $TEST == 1 ]]; then
    ./UnitTests.app
fi

# Set Compiler Back
export CC=$CC
export CXX=$CXX

