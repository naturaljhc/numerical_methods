FROM ubuntu:latest

WORKDIR /app

RUN apt-get update && \
    apt-get install -y \
    python3 \
    python3-pip \
    g++ \
    build-essential \
    libgmp-dev \
    curl \
    software-properties-common \
    git \
    cmake \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 https://github.com/symengine/symengine.git && \
    cd symengine && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install && \
    cd ../.. && \
    rm -rf symengine

COPY . .
RUN pip3 install -r requirements.txt

RUN make

EXPOSE 8501

HEALTHCHECK CMD curl --fail http://localhost:8501/_stcore/health

ENTRYPOINT ["streamlit", "run", "app.py", "--server.port=8501", "--server.address=0.0.0.0"]