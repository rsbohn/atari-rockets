{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation rec {
  name = "fujinet-lib-atari";
  version = "3.0.2";

  src = pkgs.fetchurl {
    url = "https://github.com/FujiNetWIFI/fujinet-lib/releases/download/v${version}/fujinet-lib-atari-${version}.zip";
    sha256 = "sha256-a0hiDF7I96GPFZT5BVAFa396l7Rf24n0tRFvZ5bomvM="; 
  };

  buildInputs = [ pkgs.unzip ]; 

  unpackPhase = "unzip $src";

  installPhase = ''
    mkdir -p $out/lib
    cp -r ./* $out/lib
  '';

  # Setup environment variables if needed. Adjust according to your needs.
  preFixup = ''
    export LD_LIBRARY_PATH=$out/lib:$LD_LIBRARY_PATH
  '';
}
