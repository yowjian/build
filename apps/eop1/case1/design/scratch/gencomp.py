#!/usr/bin/python3
import json

with open('design_spec.json', 'r') as inf:
  j = json.load(inf)

l = {f['flowId']:f['label'] for f in j['flows']}

for c in j['topology']:
  print (c['label'])
  for x in c['inFlows'] + c['outFlows']:
    print ('                            [ "' + l[x] + '" ],')

