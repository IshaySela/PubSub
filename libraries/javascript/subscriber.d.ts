
declare class Subscriber {
    public get remoteIp(): string;
    public get remotePort(): string;

    constructor(remoteIp:string, remotePort:number);

    /**
     * Subscribe to the endpoint and listen for data.
     * @param endpointId The id of the endpoint to subscribe to.
     * @param callback The callback will be called when data is recived.
     * @returns A promise that indicates success or failure.
     */
    public listen(endpointId:string, callback:(data:any) => void): Promise<boolean>;

}