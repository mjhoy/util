{ mkDerivation, base, directory, filepath, stdenv, unix }:
mkDerivation {
  pname = "lslink";
  version = "0.1.0.0";
  src = ./.;
  isLibrary = false;
  isExecutable = true;
  executableHaskellDepends = [ base directory filepath unix ];
  description = "List link chains";
  license = stdenv.lib.licenses.gpl2;
}
