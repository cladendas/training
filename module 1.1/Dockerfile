FROM gcc:12.2.0

RUN apt-get update && apt-get install -y \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

COPY . .

RUN mkdir build && cd build \
    && cmake -DCMAKE_CXX_STANDARD=23 .. \
    && cmake --build .
