GOJASM_BASE_URL=https://vu-oofp.gitlab.io/website/files/gojasm
PLATFORM=$(shell uname -s | tr '[:upper:]' '[:lower:]')
ARCH=$(shell uname -m)
ifeq ($(ARCH), x86_64)
	ARCH=amd64
else ifeq ($(ARCH), i686)
	ARCH=amd64
else ifeq ($(ARCH), i386)
	ARCH=i386
endif

.PHONY: gojasm clean

all: gojasm

CURL:=$(shell command -v curl 2> /dev/null)
WGET:=$(shell command -v wget 2> /dev/null)
gojasm:
ifdef WGET
	wget -O gojasm $(GOJASM_BASE_URL)/gojasm-$(PLATFORM)-$(ARCH)
else ifdef CURL
	curl -o gojasm $(GOJASM_BASE_URL)/gojasm-$(PLATFORM)-$(ARCH)
else
	$(error "Please install wget or curl.")
endif
	chmod +x gojasm

clean:
	rm -f gojasm

