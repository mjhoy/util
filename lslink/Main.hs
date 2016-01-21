module Main where

import Control.Monad
import System.Environment (getArgs)
import System.Directory
import System.IO (hPutStrLn, stderr, stdout)
import System.FilePath.Posix (takeDirectory)

import System.Posix.Files

followLinks :: Int -> String -> IO ()
followLinks level filename = do
  exists <- liftM2 (||) (doesFileExist filename) (doesDirectoryExist filename)
  case exists of
    False -> hPutStrLn stderr $ "file does not exist: " ++ filename
    True -> do
      let prefix = if level < 1 then "" else " "
      status <- getSymbolicLinkStatus filename
      absolute <- makeAbsolute filename
      hPutStrLn stdout $ prefix ++ absolute
      let isln = isSymbolicLink status
      case isln of
        True -> do
          newFilename <- readSymbolicLink filename
          absNewFilename <- makeAbsolute newFilename
          setCurrentDirectory $ takeDirectory absNewFilename
          followLinks (level + 1) newFilename
        False -> return ()

main :: IO ()
main = do
  args <- getArgs
  case args of
    [] -> hPutStrLn stderr "missing argument"
    (x:_) ->
      -- note: we should preserve current directory if doing anything
      -- after the following line.
      followLinks 0 x
