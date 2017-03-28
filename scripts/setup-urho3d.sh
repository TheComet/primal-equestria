#!/bin/sh

# The user is retarded
if [ -z "$1" ]
then
    echo "This script sets up the required symlinks in the project directory"
    echo "Usage:"
    echo "  $0 <urho3d prefix>"
    echo "Examples:"
    echo "  $0 /usr/local"
    echo "  $0 /usr/urho3d"
    exit 1
fi

# check to see if urho3d is installed
if [ ! -f "$1/include/Urho3D/Urho3D.h" ]
then
    echo "Could not find Urho3D using the prefix \"$1\""
    echo "Perhaps check if the following path to urho3d's header file exists?"
    echo "path: $1/include/Urho3D/Urho3D.h"
    exit 1
fi

# first unlink any existing links
unlink "urho3d" > /dev/null 2>&1
unlink "bin/CoreData" > /dev/null 2>&1
for f in CMake/Modules/*
do
    unlink $f > /dev/null 2>&1
done
for f in CMake/Toolchains/*
do
    unlink $f > /dev/null 2>&1
done

# do the linking
echo .gitignore > CMake/Modules/.gitignore
echo .gitignore > CMake/Toolchains/.gitignore
ln -s $1 urho3d
ln -s ../urho3d/share/Urho3D/Resources/CoreData bin/CoreData
for f in urho3d/share/Urho3D/CMake/Modules/*.cmake
do
    ln -s ../../$f CMake/Modules/$(basename $1/$f)
    echo $(basename $1/$f) >> CMake/Modules/.gitignore
done
for f in urho3d/share/Urho3D/CMake/Toolchains/*.cmake
do
    ln -s ../../$f CMake/Toolchains/$(basename $1/$f)
    echo $(basename $1/$f) >> CMake/Toolchains/.gitignore
done

