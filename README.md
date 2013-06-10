sparseMEM for large genomes
===========================

The [sparseMEM][] memory-efficient implementation by [Khan et al.][], intended to be a drop-in replacement for the `mummer` program in the [MUMmer][] program suite, offers a couple of differences in implementation:

* Economy of memory, at the cost of greater run time
* **Multithreading** of query matches

As I'm trying to align pairs of Very Large Genomes, I thought I would give MUMmer a try.  `mummer` seems to be working on the genomes "out of the box", though it is necessary to make it 64-bit compatible by following the advice [here](http://seqanswers.com/wiki/Talk:MUMmer), specifically by adding a line before `src/kurtz/libbasedir/types.h` so that lines 48-49 look like

    #define SIXTYFOURBITS
    #ifdef SIXTYFOURBITS

And `mummer` seems to be running fine... but I would still like to try a more memory-efficient alignment, especially one that offers multithreading.  Hence my use of sparseMEM.

BUT ... and here's the reason for this repository ... sparseMEM won't work "out of the box" either, but the changes required are quite a bit deeper than that for the MUMmer quite.  I've made these changes, apparently successfully, so I'm putting them here to share them.

* * *

[sparseMEM][] was developed by [Khan et al.][].  My modifications are only to enable sparseMEM to work on large genomes.  The original license of sparseMEM is found in the file `LICENSE` in the [sparseMEM zip file][], and reads in full:

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

Consider a similar license to apply to these modifications.

* * *


[sparseMEM]: http://compbio.cs.princeton.edu/mems
[sparseMEM zip file]: http://compbio.cs.princeton.edu/mems/sparseMEM.zip
[Khan et al.]: http://bioinformatics.oxfordjournals.org/content/25/13/1609.full
[MUMmer]: http://mummer.sourceforge.net