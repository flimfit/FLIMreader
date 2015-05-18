% Build the FLIMreader MEX file in the current working directory

clear FLIMreaderMex
dir = mfilename('fullpath');
dir = strrep(dir,'CompileFLIMreaderMex','');
dir = [dir 'Source' filesep];

mex([dir 'FLIMreaderMex' filesep 'FLIMreaderMex.cpp'], ...
    [dir 'FLIMReader' filesep 'PicoquantTTRReader.cpp'], ...
    [dir 'FLIMReader' filesep 'FLIMReader.cpp'], ...
    [dir 'FLIMReader' filesep 'TextReader.cpp'], ...
    ['-I' dir 'FLIMreader' ], ...
    ['-I' dir 'FLIMreaderMex'], ...
    'CXXFLAGS="$CXXFLAGS -std=c++11"');
