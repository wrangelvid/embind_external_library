FROM ubuntu:22.04
# Set environment variables.
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies.
RUN apt-get update && apt install -y npm

# Install Bazelisk via npm.
RUN npm install -g @bazel/bazelisk
