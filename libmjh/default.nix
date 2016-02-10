{ stdenv }:

stdenv.mkDerivation rec {
  name = "libmjh-0.1";

  src = ./.;

  installPhase = ''

    mkdir -p $out/lib
    mkdir -p $out/include

    cp libmjh.a $out/lib
    cp mjh_common.h $out/include
    cp get_num.h $out/include
    cp error_functions.h $out/include

  '';
}
