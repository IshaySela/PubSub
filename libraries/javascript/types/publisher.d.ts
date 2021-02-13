
declare interface PublishRequest {
    data: string | Buffer | Uint8Array;
    dataType: string;
    dataLength: number;
}


declare class Publisher {
    public get remoteIp(): string;
    public get port(): number;

    constructor(remoteIp:string, port:number);

    /**
     * Connect to the server and send the handshake data.
     */
    public connect(): Promise<boolean>;

    /**
     * Publish a request to all of the subscribers.
     * @param request The request data.
     * @returns A promise that resolves when the handshake is done..
     */
    public publish(request:PublishRequest): Promise<void>;
}