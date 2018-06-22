import cesiumpy

v = cesiumpy.CesiumWidget()

v = cesiumpy.Viewer()
b = cesiumpy.Box(dimensions=(40e4, 30e4, 50e4), material=cesiumpy.color.RED, position=[-120, 40, 0])
v.entities.add(b)#print