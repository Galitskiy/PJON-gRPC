# Client python tools

## Install gRPC and gRPC tools

```bash
apt-get install python3 python3-dev python3-venv -y
python3 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
python -m pip install grpcio
python -m pip install grpcio-tools
```

### Generate gRPC code

```bash
./run_codegen.py
```

OR

```bash
python -m grpc_tools.protoc -Iprotos --python_out=. --grpc_python_out=. protos/pjongrpc.proto
```

## Examples of run

[pjon_grpc_client.py](pjon_grpc_client.py) - client for sending requests to devices and getting responses

### Change command value

```bash
$ ./pjon_grpc_client.py 1 11 n=2
Client received: n=2>ok
```

where:

```bash
1 - master ID
11 - device ID
n=2 - command
n=2>ok - command successful
```

### Get command value

```bash
$ ./pjon_grpc_client.py 1 11 n
Client received: n>2
```

where:

```bash
1 - master ID
11 - device ID
n - command
n>2 - value 2 for command n
```

[pjon_grpc_clientserver.py](pjon_grpc_clientserver.py) - client-server script for receiving messages from devices (works in daemon mode)

```bash
$ ./pjon_grpc_clientserver.py
Client-Server received: node_id=11, data=29
```
