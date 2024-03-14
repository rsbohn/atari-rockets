{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation rec {
  name = "fujinet-lib-atari";
  version = "2.2.1";

  src = pkgs.fetchurl {
    url = "https://github.com/FujiNetWIFI/fujinet-lib/releases/download/v2.2.1/fujinet-lib-atari-2.2.1.zip";
    sha256 = "sha256-M7KeK8eG5WK/q6AUtbkT51Dqn7gnV59gzYNAiuu7sEc="; 
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