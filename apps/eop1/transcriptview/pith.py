#!/usr/bin/python3
import sys
import re
import json
import dash
import multiprocessing
import plotly.express       as px
import dash_core_components as dcc
import dash_html_components as html
import dash_cytoscape       as cyto
from   dash.dependencies    import Input, Output
from   argparse             import ArgumentParser
from   threading            import Thread

msgre = re.compile('^.*Received (.*$)')

def load_design(infile, suppmsg):
  with open(infile, 'r') as inf: j = json.load(inf)
  m   = {f['flowId']:f['message'] for f in j['flows']}
  l   = {f['flowId']:f['label'] for f in j['flows']}
  s   = {x:c['component'] for c in j['topology'] for x in c['outFlows']}
  d   = {x:c['component'] for c in j['topology'] for x in c['inFlows']}
  lvl = {x['cle-label']:x['cle-json']['level'] for x in j['cles']}

  elts = []
  for c in j['topology']: 
    elts.append({'data': {'id': c['component'], 'label': c['component'], 'level':lvl[c['label']]}})
  for x in m:             
    if not m[x] in suppmsg:
      elts.append({'data': {'source': s[x], 'target':d[x], 'label': m[x]}})
      #elts.append({'data': {'source': s[x], 'target':d[x], 'label': m[x]+':'+l[x]}})
  return elts

def update_stats(c,stats):
  for k in c:
    if not k in stats: stats[k] = 0
    stats[k] += 1

def classify(loc,rem,case,msg):
  a = {}
  a['unpart']               = True if (loc == rem) else False
  a['xd']                   = True if ('fromRemote' in msg) else False
  a['component_heartbeats'] = True if ('ss' in msg) else False
  a['sync']                 = True if ('ss' in msg) and (msg['ss'] == 'All') else False
  a['pnt']                  = True if ('time' in msg) else False
  a['groundMovers']         = True if ('bearing' in msg) else False
  a['updateMissionPlan']    = True if ('missionPlan' in msg) else False
  a['reqXXXDetections']     = True if ('phase' in msg) else False
  try: 
    a['rcvISRMDetections']  = all(d['classification'] != '' and d['speed'] != -1.0 for d in msg['detects'])
  except: 
    a['rcvISRMDetections']  = False
  try: 
    a['rcvEOIRDetections']  = all(d['classification'] != '' and d['speed'] == -1.0 for d in msg['detects'])
  except: 
    a['rcvEOIRDetections']  = False
  try: 
    a['rcvRDRDetections']   = all(d['classification'] == '' for d in msg['detects'])
  except: 
    a['rcvRDRDetections']   = False
  a['swredactdet']          = all(d['alt'] == -9999.0 for d in msg['detects'] if 'alt' in d) if 'detects' in msg else False
  a['hwredactdet']          = (a['xd'] == True and all(d['alt'] == 0.0 for d in msg['detects'] if 'alt' in d)) if 'detects' in msg else False
  try: 
    a['swredactmp']         = all([w['z'] == -9999.0 for w in msg['missionPlan']['vehiclePlan']['wayPoints']])
  except:
    a['swredactmp']         = False
  try: 
    a['hwredactmp']         = (a['xd'] == True and all([w['z'] == 0.0 for w in msg['missionPlan']['vehiclePlan']['wayPoints']]))
  except:
    a['zeroizedmp']         = False
  a['salient']              = a['sync'] or a['updateMissionPlan'] or a['reqXXXDetections'] or a['rcvRDRDetections'] or a['rcvEOIRDetections'] or a['rcvISRMDetections']
  return [i for i in a if a[i] == True]

def next_msg():
  for line in sys.stdin:
    try:
      m = msgre.match(line)
      if m:
        j = json.loads(m.group(1))
        yield j
    except:
      pass

# Parse command line argumets
def get_args():
  p = ArgumentParser(description='CLOSURE EOP Message Transcript Viewer')
  p.add_argument('-f', '--file', required=False, type=str, default='design_spec.json', help='Input file (design_spec.json)')
  p.add_argument('-s', '--suppress_messages', required=False, type=str, default='component_heartbeats,pnt,groundMovers', help='Comma-separated messages to suppress (component_heartbeats,pnt,groundMovers)')
  p.add_argument('-m', '--mode', required=False, type=str, default='txt', help='Mode can be gui or txt (txt)')
  p.add_argument('-l', '--local_enclave', required=True, type=str, help='Local enclave')
  p.add_argument('-r', '--remote_enclave', required=True, type=str, help='Remote enclave')
  p.add_argument('-c', '--case', required=True, type=str, help='EOP1 MA Demosntration Case)')
  p.add_argument('-b', '--batch_stats', required=False, type=int, default=200, help='Stats batch size (200)')
  p.add_argument('-p', '--port', required=False, type=int, default=11235, help='Dashboard port (11235)')
  return p.parse_args()

def redo_gui(app,elts):
  app.layout = html.Div([
    html.P("CLOSURE Cross-Domain Message Flow Design:"),
    cyto.Cytoscape( 
      id='cytoscape', 
      elements=elts, 
      layout={'name': 'breadthfirst'},  # breadthfirst, circle, cose, grid, ...
      stylesheet=[
        {'selector': 'node', 'style': { 'label': 'data(label)', 'background-color': 'data(level)'}},
        {'selector': 'edge', 'style': { 'width':5, 'label': 'data(label)', 'curve-style': 'bezier', 'control-point-weight': 0.9, 'target-arrow-shape': 'triangle'}}
      ],
      style={'width': '1400px', 'height': '800px'}
    )
  ])
  return app

# Run on a separate process so that it doesn't block
def start_server(app, **kwargs):
  def run():
    app.run_server(**kwargs)
  server_process = multiprocessing.Process(target=run)
  server_process.start()

if __name__ == '__main__':
  args = get_args()

  if args.mode == 'gui':
    print("#######################################################")
    print("GUI not Functional Yet")
    print("#######################################################")
    app = dash.Dash(__name__)
    elts = load_design(args.file, args.suppress_messages.split(','))
    redo_gui(app,elts)
    start_server(app,port=args.port,debug=True)
    #app.run_server(port=args.port,debug=True)

  count = 0
  stats = {}
  for m in next_msg():
    count += 1
    c = classify(args.local_enclave,args.remote_enclave,args.case,m)
    update_stats(c,stats)
    stats['count'] = count
    # if args.mode == 'gui': update_gui
    if args.mode == 'txt':
      if 'salient' in c:       print(c, ' : ', m)
      if ((count % args.batch_stats) == 0): print('Stats: ', stats)

