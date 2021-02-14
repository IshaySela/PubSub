

declare interface HandshakeResponse {
    id: string; // The id of the publisher. This data will be used to subscribe to the publisher.
    status: number; // The status of the handshake. 
}