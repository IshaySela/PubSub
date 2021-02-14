
declare interface PublishRequest {
    data: any;
    dataType: string;
    dataLength: number;
}


declare class Publisher {
    public get remoteIp(): string;
    public get port(): number;

    constructor(remoteIp:string, port:number);

    /**
     * 
     */
    public connect(): Promise<boolean>;

    /**
     * Publish a request to all of the subscribers.
     * @param request The request data.
     * @returns A promise that indicates with the request status.
     */
    public publish(request:PublishRequest): Promise<boolean>;

    /**
     * Send the handshake headers.
     */
    private handshake();
}