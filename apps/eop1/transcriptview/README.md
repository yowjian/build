# Program to analyze MA message trasncripts for cases 1 to 3

We collect messages by subscribing to the AMQ broker on all topics on both enclaves.

Invocation example:
```
# Text mode from archived file
cat transcript.orange  | python3 pith.py -l orange -r green -c case1 -b 150 -m txt -f ../case1/design/design_spec.json
# Graphics mode live
tail -f transcript.orange | python3 pith.py -l orange -r green -c case1 -b 150 -m gui -f ../case1/design/design_spec.json
# Graphics mode from archived file
awk '{print $0; system("sleep .2");} transcript.orange  | python3 pith.py -l orange -r green -c case1 -b 150 -m gui -f ../case1/design/design_spec.json
```



For details of usage:

```
python3 pith.py -h
```

