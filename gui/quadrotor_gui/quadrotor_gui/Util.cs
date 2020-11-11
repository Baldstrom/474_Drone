
namespace quadrotor_gui
{

    public static class Util
    {
        public const string ARM_CMD_STR = "ARM";
        public const string RUN_CMD_STR = "RUN";
        public const string STP_CMD_STR = "STOP";

        public enum MessageType
        {
            NA,
            AX, AY, AZ
        }

        public static MessageType GetMsgType(string msg)
        {
            string msg_type = msg.Substring(0, 2);
            switch (msg_type)
            {
                case "AX":
                    return MessageType.AX;
                case "AY":
                    return MessageType.AY;
                case "AZ":
                    return MessageType.AZ;
                default:
                    return MessageType.NA;
            }
        }
    }
}