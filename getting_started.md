<h2> Getting Started </h2>

This page provides instructions for CLOSURE development.

<h4> 1. Create your working directory </h4>

`mkdir ~/gaps`

<h4> 2. Clone the CLOSURE sources </h4>

All repositories will be switched to <b>develop</b> branch. LLVM is a large repository (over 1 Gb). It's not clear to me yet if everyone needs a checkout of LLVM but for now it is in there. We will be periodically pulling the latest LLVM and merging it into our master/develop branches as a CI task.

`cd gaps`

`gits clone http://github.com/gaps-closure`
