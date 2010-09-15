#!/bin/sh

PACKAGE=intarray
VERSION=0
CONFIG="--enable-intarray=shared"

if [ -z "$BUILDSHDIR" ]; then
	BUILDSHDIR="/galleria/sw/buildsh0"
fi

. "${BUILDSHDIR}/build_common.sh"
. "${BUILDSHDIR}/build_php.sh"

package_build $@
