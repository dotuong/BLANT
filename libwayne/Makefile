CC=gcc $(OPT) $(DEBUG) -Wall -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wstrict-prototypes -Wshadow $(PG)

default:
	# Make the same thing we made most recently
	if ls -rtlL *.a | tail -1 | grep .-g; then $(MAKE) debug; else $(MAKE) opt; fi

all:
	/bin/rm -f *.a
	# Make the pg versions (for profiling)
	$(MAKE) debug_clean
	$(MAKE) -j4 'PG=-pg' debug
	$(MAKE) opt_clean
	$(MAKE) -j4 'PG=-pg' opt
	for i in *.a; do b=`basename $$i .a`; mv $$i $$b-pg.a; done
	# Make the non-pg versions (for profiling)
	$(MAKE) debug_clean
	$(MAKE) -j4 debug
	$(MAKE) opt_clean
	$(MAKE) -j4 opt
	if [ ! -x bin/stats ]; then (cd tests; make stats; mv stats ../bin); fi
	touch made

opt:
	$(MAKE) 'OPT=-O3' 'LIBOUT=libwayne.a' libwayne

debug:
	$(MAKE) 'DEBUG=-ggdb' 'LIBOUT=libwayne-g.a' libwayne

libwayne:
	$(MAKE) $(LIBOUT)
	mv src/$(LIBOUT) .
	[ `arch` = Darwin ] || ar r $(LIBOUT)

debug_clean:
	$(MAKE) 'DEBUG=-ggdb' 'LIBOUT=libwayne-g.a' raw_clean

opt_clean:
	$(MAKE) 'OPT=-O3' 'LIBOUT=libwayne.a' raw_clean

raw_clean:
	/bin/rm -f src/*.[oa] $(LIBOUT) made
	cd MT19937; $(MAKE) clean

clean:
	/bin/rm -f *.a
	$(MAKE) debug_clean
	$(MAKE) opt_clean
	/bin/rm -f made

$(LIBOUT): src/$(LIBOUT)
	ranlib src/$(LIBOUT)

src/$(LIBOUT):
	cd src; $(MAKE) 'CC=$(CC)' 'LIBOUT=$(LIBOUT)' 'DEBUG=$(DEBUG)'
