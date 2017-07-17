@echo off

set command1=git add .
set command2=git commit -m %1
set command3=git push -u origin master

pushd ..

%command1%

%command2%

%command3%

popd