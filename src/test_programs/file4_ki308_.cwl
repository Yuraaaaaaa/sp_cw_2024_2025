NAME _PROGRAM ; 
BODY DATA INTEGER16 _AAAAAAA ;
  GET ( _AAAAAAA )
  WHILE _AAAAAAA >= 1
    _AAAAAAA - 1 >> _AAAAAAA
    PUT ( _AAAAAAA )
  END WHILE
END
