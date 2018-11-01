# @@@ START COPYRIGHT @@@
#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#
# @@@ END COPYRIGHT @@@

# Makefile for building Type 2 driver native code on Linux
#

include $(TRAF_HOME)/macros.gmk # top level
include ./macros.gmk

#
# Source files required to build sql server:

COMMON_OBJS  =
OUTDIR = ./obj
#LIBEXPDIR = .
T2_OBJS  = $(OUTDIR)/CommonDiags.o \
       $(OUTDIR)/Debug.o \
       $(OUTDIR)/CSrvrConnect.o \
       $(OUTDIR)/CSrvrStmt.o \
       $(OUTDIR)/SqlInterface.o \
       $(OUTDIR)/InterfaceConnection.o \
       $(OUTDIR)/SrvrCommon.o \
       $(OUTDIR)/SrvrOthers.o \
       $(OUTDIR)/TestInterface.o \
       $(OUTDIR)/SrvrKds.o \
       $(OUTDIR)/Connection.o \
       $(OUTDIR)/SrvrFunctions.o \
       $(OUTDIR)/JdbcDriverGlobal.o \
       $(OUTDIR)/InterfaceDriver.o \
       $(OUTDIR)/SrvrSmd.o \
       $(OUTDIR)/InterfaceCommonFunctions.o \
       $(OUTDIR)/GlobalInformation.o  
OBJS = $(COMMON_OBJS) $(T2_OBJS)
MXODIR = $(TRAF_HOME)/../conn/odbc/src/odbc

INCLUDES     = -I. -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -Inative -I$(MXODIR)/Krypton/generated_incs -I$(MXODIR)/dependencies/windows -I$(MXODIR)/dependencies/include -I$(MXODIR)/dependencies/linux -I$(TRAF_HOME)/export/include/sql -I$(TRAF_HOME)/inc/tmf_tipapi -I$(TRAF_HOME)/inc -I$(TRAF_HOME)/export/include/nsk -I$(TRAF_HOME)/export/include -I$(TRAF_HOME)/inc/rosetta -I$(TRAF_HOME)/../sql/cli -I$(TRAF_HOME)/../sql/common -I$(TRAF_HOME)/../dbsecurity/cert/inc -I$(TRAF_HOME)/../dbsecurity/auth/inc -I$(TRAF_HOME)/commonLogger  -I$(LOG4CXX_INC_DIR) -I$(LOG4CXX_INC_DIR)/lib4cxx
COMMON_DEFINES = -DTRAFODION_JDBCT2_VER_MAJOR=$(TRAFODION_VER_MAJOR) -DTRAFODION_JDBCT2_VER_MINOR=$(TRAFODION_VER_MINOR) -D_LP64 -DNA_LINUX -DSIZEOF_LONG_INT=4 -DSQ_GUARDIAN_CALL -DDISABLE_NOWAIT -D_FASTPATH -DTODO -D_SQ64 -w

DEFINES =  $(COMMON_DEFINES)

CODEGEN = -fPIC

.PHONY: all

LN :=/bin/ln -sf
JAVAH :=$(JAVA_HOME)/bin/javah
EXPROOT :=  ${TRAF_HOME}/export
CP := /bin/cp -f
all: test 


test: $(OBJS)
	$(CXX) -o $@ -L$(LIBEXPDIR) -lsbfs -lsbms -levlsq -lwin -ltdm_sqlcli  -larkcmp_dll -larkcmplib -lcommon -lsort -lexecutor -lcomexe -lcli $(OBJS)

ide:
	cp test ./bin/Debug

clean:
	$(RM) -rf $(OUTDIR)
