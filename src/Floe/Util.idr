module Floe.Util

-- Common utility functions

-----------------------------------------------------------
-- Maybe/Either conversions
-----------------------------------------------------------

-- Convert Maybe to Either with error
public export
note : err -> Maybe a -> Either err a
note err Nothing  = Left err
note _   (Just x) = Right x
