# default.nix for 'rockets'
let
  pkgs = import <nixpkgs> { };
  fujinet = import ./fujinet-lib-atari.nix { inherit pkgs; };
in pkgs.stdenv.mkDerivation {
  pname = "atari-rocket-launch";
  version = "0.1.0";
  src = ./.;

  buildInputs = [ pkgs.cc65 ];

  buildPhase = ''
    FUJINET_LIB=${fujinet}/lib make rockets.xex
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp rockets.xex $out/bin
  '';
}
