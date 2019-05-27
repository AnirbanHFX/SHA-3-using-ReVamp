import json
data = dict()

data['dim'] = dict()
data['dim']['m'] = 42
data['dim']['n'] = 64

data['filename'] = dict()
data['filename']['ins_mem'] = 'Keccak-f1600.ins'
data['filename']['input']   = 'Keccak-f1600.inp'
data['filename']['output']  = 'Keccak-f1600'

data['voltage'] = dict()
data['voltage']['1'] = 2.4
data['voltage']['0']  = -2.4
data['voltage']['period']    = 50 # unit is nanoseconds
data['voltage']['delta']    = 5

data['simulation']   = dict()
data['simulation']['cycles'] = 0 #n; if n=0, then all instructions; If n>0 , n instructions 
data['simulation']['verbose'] = 0 #v; if v=0, not verbose; if v>0, print crossbar state every v cycles
data['simulation']['print_ins'] = 1 #k;if k=0, do not print instruction; else print instruction


with open('config_data.json', 'w') as outfile:  
    json.dump(data, outfile,indent=4,sort_keys=True)
