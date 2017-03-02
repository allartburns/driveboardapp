__author__ = 'jet <jet@allartburns.org>'

class DBAPass:
    """model for abstract DBA entries
       docs/dba.md for definition
    """

    def __init__(self):
          # from the dba.md file, using defaults
          self.passDetails = {
                'items': [], 
                'relative': False,
                'seekrate': 0,
                'feedrate': 0,
                'intensity': 0,
                'pierce_time': 0,
                'pxsize': 0.0,
                'air_assist': "pass",
                'aux1_assist': "off"
                }
          self.defs = []
          self.item = {
                'def': 0,
                'translate':[],
                'color':""
                }
          
          
    def SetPassDetails(self, items, seekrate, feedrate, intensity,
                pierce_time = 0, relative = False, pxsize = 0.4,
                       air_assist = "pass", aux1_assist = "off"):
        self.passDetails['items'] = items
        self.passDetails['relative'] = relative
        self.passDetails['seekrate'] = seekrate
        self.passDetails['feedrate'] = feedrate
        self.passDetails['intensity'] = intensity
        self.passDetails['pierce_time'] = pierce_time
        self.passDetails['pxsize'] = pxsize
        self.passDetails['air_assist'] = air_assist
        self.passDetails['aux1_assist'] = aux1_assist


    def PassDetails(self):
        return self.passDetails
    
    def AddDef(self, defs):
        if len(defs) > 0:
            self.defs.append(defs)


    def Defs(self):
        return self.defs

            
    def SetItem(self, defs, color = "", translate = [0, 0, 0]):
        self.item['def'] = defs
        self.item['color'] = color
        self.item['translate'] = translate

        
    def Item(self):
        return self.item

    
    def Pass(self):
        job = {'passes':[], 'items':[], 'defs':[]}
        job['passes'] = self.passDetails
        job['items'] = self.items
        job['defs'] = self.stats

        return job


