#Design procedure to be converted into CVI tasks

mkdir -p ../xdcc/egress_xdcc/xdcc_autogen
mkdir -p ../xdcc/ingress_xdcc/xdcc_autogen
mkdir -p ../xdcc/xdcc_echo

cat << EOT > config.json
{
    "egressDir": "../xdcc/egress_xdcc/xdcc_autogen",
    "ingressDir": "../xdcc/ingress_xdcc/xdcc_autogen",
    "echoDir": "../xdcc/xdcc_echo",
    "enclave": "orange",
    "xdccFlow": "design_spec.json"
}
EOT

/opt/closure/bin/xdcc_gen -c config.json
