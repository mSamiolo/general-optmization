#!/usr/bin/python3

##### It manually creates a VTU (VTK Unstructured Grid) file, a common format for 3D scientific data 
##### visualization. It writes specific geometric and data information into this file.

import struct
import binascii as ba

FILE = "data/case/results/test_from_make_vtu.py.vtu"

def write_default_vtk():
	try:
		## MS Insertion - Chnaged 'wb' to 'w'
		binfile = open(FILE,'wb')
	except Exception:
		exit("Couldn't create file...")

	writeHeader(binfile,4,1)
	lP = [0, 0, 0, 2, 0, 0, 0, 0, 2, 1, 1, 1]
	writePoints(binfile,lP)
	lConn =[0, 1, 2, 3]
	lOffset = [4]
	lTypes = [10]
	writeCells(binfile,lConn,lOffset,lTypes)
	lldata = []
	lldata.append(["Scalars",1,2,-1,0.5])
	lldata.append(["OtherSet",1.0,2,3,127.3])
	writeScalarPointData(binfile,lldata)
	lldata = []
	lldata.append(["Scalars",1.0])
	lldata.append(["Scalars2",27.0])
	writeScalarCellData(binfile,lldata)
	writeFooter(binfile)
	binfile.close()


	# nP = number of points
	# nC = number of cells
def writeHeader(binfile,nP,nC):
	binfile.write(b"<?xml version=\"1.0\"?>\n")
	binfile.write(b"<VTKFile type=\"UnstructuredGrid\" version=\"1.0\" header_type=\"UInt64\" byte_order=\"LittleEndian\">\n")
	binfile.write(b"<UnstructuredGrid>\n")
	point_and_cells="\t<Piece NumberOfPoints=\"" + str(nP) +"\" NumberOfCells=\"" + str(nC) + "\">\n"
	binfile.write(point_and_cells.encode())


def writeFooter(binfile):
	binfile.write(b"\t</Piece>\n")
	binfile.write(b"</UnstructuredGrid>\n")
	binfile.write(b"</VTKFile>")


def writeRawPoints(binfile,data):
	binfile.write(b"\t\t<Points>\n")
	binfile.write(b"\t\t\t<DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"binary\">\n")
	binfile.write(writeBin64(data))
	binfile.write(b"\t\t\t</DataArray>\n")
	binfile.write(b"\t\t</Points>\n")


#lP = list of points
#3D coordinates assumed...
def writePoints(binfile,lP):
	binfile.write(b"\t\t<Points>\n")
	binfile.write(b"\t\t\t<DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"binary\">\n")
	data = b""
	#Append number to binary datalist
	for number in lP:
		data += struct.pack('f',number)
	binfile.write(writeBin64(data))
	binfile.write(b"\t\t\t</DataArray>\n")
	binfile.write(b"\t\t</Points>\n")

#lConn = connectivity list
#lOffset = Offset list
def writeCells(binfile,lConn,lOffset,lTypes):
	binfile.write(b"\t\t<Cells>\n")
	binfile.write(b"\t\t\t<DataArray type=\"UInt32\" Name=\"connectivity\" format=\"binary\">\n")
	data = b""
	for number in lConn:
		data += struct.pack('I',number)
	binfile.write(writeBin64(data))
	binfile.write(b"\t\t\t</DataArray>\n")

	binfile.write(b"\t\t\t<DataArray type=\"UInt32\" Name=\"offsets\" format=\"binary\">\n")
	data = b""
	for number in lOffset:
		data += struct.pack('I',number)
	binfile.write(writeBin64(data))
	binfile.write(b"\t\t\t</DataArray>\n")

	#Data type could be UInt8 instead, but UInt32 keeps it simple for now...
	binfile.write(b"\t\t\t<DataArray type=\"UInt32\" Name=\"types\" format=\"binary\">\n")
	data = b""
	for number in lTypes:
		data += struct.pack('I',number)
	binfile.write(writeBin64(data))
	binfile.write(b"\t\t\t</DataArray>\n")
	binfile.write(b"\t\t</Cells>")



def writeRawCellsConn(binfile,data):
	binfile.write(b"\t\t<Cells>\n")
	binfile.write(b"\t\t\t<DataArray type=\"UInt64\" Name=\"connectivity\" format=\"binary\">\n")
	binfile.write(writeBin64(data))
	binfile.write(b"\t\t\t</DataArray>\n")

def writeRawCellsOffset(binfile,data):
	binfile.write(b"\t\t\t<DataArray type=\"UInt64\" Name=\"offsets\" format=\"binary\">\n")
	binfile.write(writeBin64(data))
	binfile.write(b"\t\t\t</DataArray>\n")

def writeRawCellsType(binfile,data):
	binfile.write(b"\t\t\t<DataArray type=\"UInt64\" Name=\"types\" format=\"binary\">\n")
	binfile.write(writeBin64(data))
	binfile.write(b"\t\t\t</DataArray>\n")
	binfile.write(b"\t\t</Cells>")

# Returns Int containing data size + data
# everything in base64 encoding
def writeBin64(bindata):
	datalen = struct.pack('Q',len(bindata))
	# Note that \n is removed from datalen
	# - which btw is a ridiculous design choice
	# as it makes the data size grow by 33% (4/3-1)
	return ba.b2a_base64(datalen)[0:-1]+ba.b2a_base64(bindata)


	##lldata = list of list of data (where 1st entry is set name)
def writeScalarPointData(binfile,lldata):
	binfile.write(b"\t\t<PointData Scalars=\"scalars\">\n")

	for ldata in lldata:
		setname = ldata[0]
		del ldata [0]
		data = b""
		for number in ldata:
			data += struct.pack('f',number)
		text=str("\t\t\t<DataArray type=\"Float32\" Name=\"" + setname + "\" format=\"binary\">\n")
		binfile.write(text.encode())
		binfile.write(writeBin64(data))
		binfile.write(b"\t\t\t</DataArray>\n")
	
	binfile.write(b"\t\t</PointData>\n")


def writeRawScalarPointData(binfile,ldata,setnames):
	binfile.write(b"\t\t<PointData Scalars=\"scalars\">\n")

	j=-1
	for data in ldata:
		j=j+1
		binfile.write(b"\t\t\t<DataArray type=\"Float32\" Name=\"" + setnames[j] + "\" format=\"binary\">\n")
		binfile.write(writeBin64(data))
		binfile.write(b"\t\t\t</DataArray>\n")
	
	binfile.write(b"\t\t</PointData>\n")


def writeScalarCellData(binfile,lldata):
	binfile.write(b"\t\t<CellData Scalars=\"scalars\">\n")

	for ldata in lldata:
		setname = ldata[0]
		del ldata [0]
		data = b""
		for number in ldata:
			data += struct.pack('f',number)
		text = str("\t\t\t<DataArray type=\"Float32\" Name=\"" + setname + "\" format=\"binary\">\n")
		binfile.write(text.encode())
		binfile.write(writeBin64(data))
		binfile.write(b"\t\t\t</DataArray>\n")

	binfile.write(b"\t\t</CellData>\n")


def writeRawScalarCellData(binfile,ldata,setnames):
	binfile.write("\t\t<CellData Scalars=\"scalars\">\n")

	j=-1
	for data in ldata:
		j=j+1
		binfile.write(b"\t\t\t<DataArray type=\"Float32\" Name=\"" + setnames[j] + "\" format=\"binary\">\n")
		binfile.write(writeBin64(data))
		binfile.write(b"\t\t\t</DataArray>\n")

	binfile.write(b"\t\t</CellData>\n")


if __name__ == "__main__":
	write_default_vtk()
	print("Written a VTU file at: ", FILE)

