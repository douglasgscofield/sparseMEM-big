sparseMEM-big : sparseMEM for large genomes
===========================

**NOTE: This branch (godotgildor-fork) does not currently compile for me on my iMac, boost link problems.**


A [suffix array][] can be a useful data structure for representing sequence content.  [MUMmer][] is perhaps the best-known tool to use suffix arrays, but the speed and capacity of MUMmer can be improved upon, given some trade-offs.  [sparseMEM][] offers a drop-in replacement for the `mummer` program that is reported to be more memory-efficient than that in MUMmer, with a couple of differences:

* Economy of memory, at the cost of greater run time
* **Multithreading** of query matches

As I'm trying to align pairs of Very Large Genomes, I thought I would give MUMmer or something similar a try.  The `mummer` program seems to be working on the genomes, though it is necessary to make it 64-bit compatible by following the advice [here](http://seqanswers.com/wiki/Talk:MUMmer), by adding a line before `src/kurtz/libbasedir/types.h` so that lines 48-49 look like

    #define SIXTYFOURBITS
    #ifdef SIXTYFOURBITS

Kudos to MUMmer's developers for taking this into account.  I would still like to try a more memory-efficient alignment, especially one that offers multithreading.  Hence my use of sparseMEM.

BUT ... and here's the reason for this repository ... sparseMEM won't work "out of the box."  It fails for the large (~20Gbp) genomes I am trying to align.

**NOTE**: it still fails, even with the changes contained here... I have no explicit message for the latest failure beyond "`Killed`".  Judging from `htop` what may have happened is that it wanted too much memory, last I checked it was using close to 1TB on a 1TB machine.


## Changes from sparseMEM

The changes required to get sparseMEM to work for such large genomes are quite a bit more extensive than for the MUMmer suite, but no more complicated.  They are easily compartmentalised by using `typedef` similar to MUMmer, so that's what I've done in the code available here.

Another change from sparseMEM is that the built executable is named `mummer-sparseMEM-big`, rather than `mummer` as in the original sparseMEM release.

This executable has support for large genomes enabled by default.  You can disable this in the `Makefile` by removing the `-DSIXTYFOURBITS` flag from `FLAGS`.  Note that the name of the executable will remain as above.


## Other MUMmer Alternatives

I haven't tried any of these tools, but maybe you will.

[essaMEM][] by [Vyverman et al.][] offers further memory economy.

[backwardMEM][] by [Ohlebusch et al.][] is reported by [Vyverman et al.][] to outperform sparseMEM unless abundant memory is available, but the developers note at the [backwardMEM][] download site that it is not currently capable of handling genomes > 2Gbp.

[vmatch](http://www.vmatch.de) is closed-source.


## License

[sparseMEM][] was developed by [Khan et al.][]  My modifications are only to enable sparseMEM to work on large genomes.  The original license of sparseMEM is found in the file `LICENSE` in this repository, as well as in the [sparseMEM zip file][] at the developers' download site, and reads in full:

<pre>
* Copyright (c) 2009, Princeton University
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the Princeton University nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY Princeton University ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL Princeton University BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

</pre>

Consider a similar license to apply to these modifications, with this added
copyright applying to my changes only.
<pre>
* Copyright (c) 2013, Douglas G. Scofield, douglasgscofield@gmail.com
</pre>

* * *

[suffix array]:       http://en.wikipedia.org/wiki/Suffix_array
[sparseMEM]:          http://compbio.cs.princeton.edu/mems
[sparseMEM zip file]: http://compbio.cs.princeton.edu/mems/sparseMEM.zip
[Khan et al.]:        http://bioinformatics.oxfordjournals.org/content/25/13/1609.short
[MUMmer]:             http://mummer.sourceforge.net
[essaMEM]:            https://github.ugent.be/ComputationalBiology/essaMEM
[Vyverman et al.]:    http://bioinformatics.oxfordjournals.org/content/29/6/802.short
[backwardMEM]:        view-source:http://www.uni-ulm.de/in/theo/research/seqana.html
[Ohlebusch et al.]:   https://www.uni-ulm.de/fileadmin/website_uni_ulm/iui.inst.190/Mitarbeiter/ohlebusch/PAPERS/SPIRE11a.pdf

